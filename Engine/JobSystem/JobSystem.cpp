#include "JobSystem.h"

#include <thread>

#include "JobContainer.h"

namespace JobSystem
{
    struct Job
    {
        Ñontext* ctx;
        std::function<void(JobArgs)> task;
        uint32_t groupID;
        uint32_t groupJobOffset;
        uint32_t groupJobEnd;
        uint32_t sharedMemorySize;
    };

    uint32_t numThreads = 0;
    JobContainers::ThreadSafeRingBuffer<Job, 256> jobQueue;
    std::condition_variable wakeCondition;
    std::mutex wakeMutex;

    // This function executes the next item from the job queue. Returns true if successful, false if there was no job available
    inline bool Work()
    {
        Job job;
        if (jobQueue.pop_front(job))
        {
            JobArgs args;
            args.groupID = job.groupID;
            if (job.sharedMemorySize > 0)
            {
                args.sharedMemory = alloca(job.sharedMemorySize);
            }
            else
            {
                args.sharedMemory = nullptr;
            }

            for (uint32_t i = job.groupJobOffset; i < job.groupJobEnd; ++i)
            {
                args.jobIndex = i;
                args.groupIndex = i - job.groupJobOffset;
                args.isFirstJobInGroup = (i == job.groupJobOffset);
                args.isLastJobInGroup = (i == job.groupJobEnd - 1);
                job.task(args);
            }

            job.ctx->counter.fetch_sub(1);
            return true;
        }
        return false;
    }

    void Initialize()
    {
        // Retrieve the number of hardware threads in this system:
        auto numCores = std::thread::hardware_concurrency();

        // Calculate the actual number of worker threads we want (-1 main thread):
        numThreads = std::max(1u, numCores - 1);

        // Lambda function for thread infinity loop
        auto threadLoop
        {
            []
            {
                while (true)
                {
                    if (!Work())
                    {
                        // no job, put thread to sleep
                        std::unique_lock<std::mutex> lock(wakeMutex);
                        wakeCondition.wait(lock);
                    }
                }

            }
        };
        
        for (uint32_t threadID = 0; threadID < numThreads; ++threadID)
        {
            std::thread worker(threadLoop);
            
            worker.detach();
        }
    }

    uint32_t GetThreadCount()
    {
        return numThreads;
    }

    void Execute(Ñontext& ctx, const std::function<void(JobArgs)>& task)
    {
        // Context state is updated:
        ctx.counter.fetch_add(1);

        Job job;
        job.ctx = &ctx;
        job.task = task;
        job.groupID = 0;
        job.groupJobOffset = 0;
        job.groupJobEnd = 1;
        job.sharedMemorySize = 0;

        // Try to push a new job until it is pushed successfully:
        while (!jobQueue.push_back(job)) { wakeCondition.notify_all(); }

        // Wake any one thread that might be sleeping:
        wakeCondition.notify_one();
    }

    void Dispatch(Ñontext& ctx, uint32_t jobCount, uint32_t groupSize, const std::function<void(JobArgs)>& task, size_t sharedMemorySize)
    {
        if (jobCount == 0 || groupSize == 0)
        {
            return;
        }

        const uint32_t groupCount = DispatchGroupCount(jobCount, groupSize);

        // Context state is updated:
        ctx.counter.fetch_add(groupCount);

        Job job;
        job.ctx = &ctx;
        job.task = task;
        job.sharedMemorySize = (uint32_t)sharedMemorySize;

        for (uint32_t groupID = 0; groupID < groupCount; ++groupID)
        {
            // For each group, generate one real job:
            job.groupID = groupID;
            job.groupJobOffset = groupID * groupSize;
            job.groupJobEnd = std::min(job.groupJobOffset + groupSize, jobCount);

            // Try to push a new job until it is pushed successfully:
            while (!jobQueue.push_back(job)) { wakeCondition.notify_all(); }
        }

        // Wake any threads that might be sleeping:
        wakeCondition.notify_all();
    }

    uint32_t DispatchGroupCount(uint32_t jobCount, uint32_t groupSize)
    {
        // Calculate the amount of job groups to dispatch (overestimate, or "ceil"):
        return (jobCount + groupSize - 1) / groupSize;
    }

    bool IsBusy(const Ñontext& ctx)
    {
        // Whenever the context label is greater than zero, it means that there is still work that needs to be done
        return ctx.counter.load() > 0;
    }

    void Wait(const Ñontext& ctx)
    {
        // Wake any threads that might be sleeping:
        wakeCondition.notify_all();

        // Waiting will also put the current thread to good use by working on an other job if it can:
        while (IsBusy(ctx)) { Work(); }
    }
}

#pragma once

#include <functional>
#include <atomic>

struct JobArgs
{
    uint32_t jobIndex;		// job index relative to dispatch (like SV_DispatchThreadID in HLSL)
    uint32_t groupID;		// group index relative to dispatch (like SV_GroupID in HLSL)
    uint32_t groupIndex;	// job index relative to group (like SV_GroupIndex in HLSL)
    bool isFirstJobInGroup;	// is the current job the first one in the group?
    bool isLastJobInGroup;	// is the current job the last one in the group?
    void* sharedMemory;		// stack memory shared within the current group (jobs within a group execute serially)
};

namespace JobSystem
{

    void Initialize();

    uint32_t GetThreadCount();

    // Defines a state of execution, can be waited on
    struct Context
    {
        std::atomic<uint32_t> counter{ 0 };
    };

    // Add a task to execute asynchronously. Any idle thread will execute this.
    void Execute(const std::function<void(JobArgs)>& task);

    // Divide a task onto multiple jobs and execute in parallel.
    //	jobCount	: how many jobs to generate for this task.
    //	groupSize	: how many jobs to execute per thread. Jobs inside a group execute serially. It might be worth to increase for small jobs
    //	task		: receives a wiJobArgs as parameter
    void Dispatch(uint32_t jobCount, uint32_t groupSize, const std::function<void(JobArgs)>& task, size_t sharedMemorySize = 0);

    // Returns the amount of job groups that will be created for a set number of jobs and group size
    uint32_t DispatchGroupCount(uint32_t jobCount, uint32_t groupSize);

    // Check if any threads are working currently or not
    bool IsBusy();

    // Wait until all threads become idle
    void Wait();

}
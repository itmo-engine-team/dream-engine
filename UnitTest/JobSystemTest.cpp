#include "pch.h"

#include "JobSystem.h"
#include <chrono>

using namespace std;

void Spin(float milliseconds)
{
    milliseconds /= 1000.0f;
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    double ms = 0;
    while (ms < milliseconds)
    {
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
        ms = time_span.count();
    }
}

struct timer
{
    string name;
    chrono::high_resolution_clock::time_point start;

    timer(const string& name) : name(name), start(chrono::high_resolution_clock::now()) {}
    ~timer()
    {
        auto end = chrono::high_resolution_clock::now();
        cout << name << ": " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds" << endl;
    }
};

struct Data
{
    float m[16];
    void Compute(uint32_t value)
    {
        for (int i = 0; i < 16; ++i)
        {
            m[i] += float(value + i);
        }
    }
};

TEST(JobSystemTest, InitTest)
{
    JobSystem::Initialize();

    cout << JobSystem::GetThreadCount() << endl;
}

TEST(JobSystemTest, ExecuteTest)
{
    JobSystem::Initialize();

    // Serial test
    {
        auto t = timer("Serial test: ");

        Spin(100);
        Spin(100);
        Spin(100);
        Spin(100);
    }

    // Execute test
    {
        auto t = timer("Execute() test: ");
        
        JobSystem::Execute([](JobArgs args){ Spin(100); });
        JobSystem::Execute([](JobArgs args){ Spin(100); });
        JobSystem::Execute([](JobArgs args){ Spin(100); });
        JobSystem::Execute([](JobArgs args){ Spin(100); });
        JobSystem::Wait();
    }
}

TEST(JobSystemTest, DispatchTest)
{
    const uint32_t dataCount = 100000000;

    // Loop test:
    {
        Data* dataSet = new Data[dataCount];
        {
            auto t = timer("Loop test: ");

            for (uint32_t i = 0; i < dataCount; ++i)
            {
                dataSet[i].Compute(i);
            }
        }
        delete[] dataSet;
    }

    {
        JobSystem::Initialize();
        Data* dataSet = new Data[dataCount];
        {
            auto t = timer("Dispatch() test: ");

            const uint32_t groupSize = 500000;
            JobSystem::Dispatch(dataCount, groupSize, [&dataSet](JobArgs args) {
                dataSet[args.jobIndex].Compute(args.jobIndex);
            }, 0);
            
            JobSystem::Wait();
            
        }
        delete[] dataSet;
    }
}
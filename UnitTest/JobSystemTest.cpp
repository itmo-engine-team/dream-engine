#include "pch.h"
//#include "JobSystem/JobSystem.h"
#include <iostream>
#include <chrono>
#include <string>

//struct timer
//{
//    std::string name;
//    std::chrono::high_resolution_clock::time_point start;
//
//    timer(const  std::string& name) : name(name), start(std::chrono::high_resolution_clock::now()) {}
//    ~timer()
//    {
//        auto end = std::chrono::high_resolution_clock::now();
//        std::cout << name << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
//    }
//};
//
//struct Data
//{
//    float m[16];
//    void Compute(uint32_t value)
//    {
//        for (int i = 0; i < 16; ++i)
//        {
//            m[i] += float(value + i);
//        }
//    }
//};
//uint32_t dataCount = 1000000;
//
//
//
//int JobSystemTest()
//{
//    JobSystem::Initialize();
//
//    JobSystem::Context finishedLabel;
//    // Loop test:
//    {
//        Data* dataSet = new Data[dataCount];
//        {
//            auto t = timer("loop test: ");
//
//            for (uint32_t i = 0; i < dataCount; ++i)
//            {
//                dataSet[i].Compute(i);
//            }
//        }
//        delete[] dataSet;
//    }
//
//    // Dispatch test:
//    {
//        Data* dataSet = new Data[dataCount];
//        {
//            auto t = timer("Dispatch() test: ");
//
//            const uint32_t groupSize = 1000;
//            JobSystem::Execute(finishedLabel, [&dataSet](JobArgs args) {
//                dataSet[args.jobIndex].Compute(1);
//                });
//            JobSystem::Wait(finishedLabel);
//        }
//        delete[] dataSet;
//    }
//    return 0;
//}
//
//
//
//TEST(TestCaseName, TestName) {
//  EXPECT_EQ(1, 1);
//  EXPECT_TRUE(true);
//}
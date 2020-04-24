#include "Benchmark.h"

void RaiiTimer::Stop()
{
    auto endTimePoint = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    auto duration = end - start;
    double ms = duration * 0.001;
    std::cout << "Duration in " << ms << "ms" << std::endl;
    std::cout << "Duration in  " << duration << "us" << std::endl;
}

RaiiTimer::~RaiiTimer()
{
    Stop();
}

RaiiTimer::RaiiTimer()
{
    m_StartTimePoint = std::chrono::high_resolution_clock::now();
}

CallbackTimer::CallbackTimer()
{
}
void CallbackTimer::Benchmark(std::function<void()> callback)
{
    this->Start();
    callback();
    this->Stop();
}

void CallbackTimer::Start()
{
    m_StartTimePoint = std::chrono::high_resolution_clock::now();
}
void CallbackTimer::Stop()
{
    auto endTimePoint = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    auto duration = end - start;
    double ms = duration * 0.001;
    std::cout << "Duration in " << ms << "ms" << std::endl;
    std::cout << "Duration in  " << duration << "us" << std::endl;
}
#ifndef MYDB_BENCHMARK_H
#define MYDB_BENCHMARK_H

#include <chrono>
#include <iostream>
#include <functional>

class RaiiTimer
{

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;

public:
    void Stop();
    ~RaiiTimer();
    RaiiTimer();
};

class CallbackTimer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;

    void Start();
    void Stop();
public:
    CallbackTimer();
    template <class T>
    T Benchmark(std::function<T> callback);
};

#endif
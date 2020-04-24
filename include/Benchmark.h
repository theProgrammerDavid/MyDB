#ifndef MYDB_BENCHMARK_H
#define MYDB_BENCHMARK_H

#include <chrono>
#include <iostream>

class RaiiTimer {

private:
	std::chrono::time_point<std::chrono::high_resolution_clock>m_StartTimePoint;

public:


	void Stop();

	~RaiiTimer();

	RaiiTimer();
};

#endif
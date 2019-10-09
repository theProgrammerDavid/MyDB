#pragma once
#include <thread>
#include <iostream>

class thread_guard {

	std::thread& t;

public:

	explicit thread_guard(std::thread& t_) :t(t_) {}
	~thread_guard() {
		if (t.joinable()) {
			t.join();
			//this ensures that join() is the last function that is called
		}

		
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
	//this ensures that the default assignment and copy constructor are not provided by the compiler
	//as we do not want this object to be copied or outlive the thread that it is joining
};

class scoped_thread {
	std::thread t;

public:
	explicit scoped_thread(std::thread t_) :t(std::move(t_)) {
		if (!t.joinable()) {
			throw std::logic_error("Invalid thread passed");
		}
	}

	~scoped_thread() {
		t.join();
	}

	scoped_thread(scoped_thread const&) = delete;
	scoped_thread& operator=(scoped_thread const&) = delete;
};
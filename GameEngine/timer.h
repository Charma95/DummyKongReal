#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include <functional>


class timer
{
	
	public:
		timer();
		timer(std::function<void(void)> func, const long &interval);
		~timer();
		void start(); 
		void stop(); 
		void restart();
		bool isRunning(); 
		timer *setFunc(std::function<void(void)> func);
		long getInterval();
		timer *setInterval(const long &interval);
		long getElapsedTime();
		void setElapsedTime(long newElapsedTime);

	private:
		// Function to be executed fater interval
		std::function<void(void)> m_func;
		long m_interval;
		std::thread m_thread;
		bool m_running = false;
		long elapsedTime;
	};


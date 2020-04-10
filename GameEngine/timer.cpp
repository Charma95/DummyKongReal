#include "timer.h"


timer::timer()
{

}

timer::timer(std::function<void(void)> func, const long &interval)
{
	m_func = func;
	m_interval = interval;
}

timer::~timer()
{
	stop();
}

void timer::start() 
{
	m_running = true;
	m_thread = std::thread([&]() 
	{
		while (m_running) 
		{
			auto delta = std::chrono::steady_clock::now() + std::chrono::milliseconds(m_interval);
			m_func();
			std::this_thread::sleep_until(delta);
		}
	});
	m_thread.detach();
}

void timer::stop()
{
	m_running = false;
	m_thread.~thread();
}

void timer::restart() 
{
	stop();
	start();
}

bool timer::isRunning() 
{
	return m_running;
}

timer* timer::setFunc(std::function<void(void)> func)
{
	m_func = func;
	return this;
}

long timer::getInterval()
{
	return m_interval;
}

timer * timer::setInterval(const long &interval)
{
	m_interval = interval;
	return this;
}

long timer::getElapsedTime()
{
	return elapsedTime;
}

void timer::setElapsedTime(long newElapsedTime)
{
	elapsedTime = newElapsedTime;
}

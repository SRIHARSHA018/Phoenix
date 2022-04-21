#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>

class Time
{
private:
	static float x_last_time;
	static float x_delta_time;
	~Time() {}
private:
	Time() {}
public:
	static void updateDeltaTime();
	static const float getDeltaTime();
};



namespace Chrono {
	class Timer {
	public:
		Timer() {
			auto start = std::chrono::high_resolution_clock::now();
		}
		~Timer() {
		}
	};
}
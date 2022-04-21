#include "Global.h"

float Time::x_last_time = 0.f;
float Time::x_delta_time = 0.f;

void Time::updateDeltaTime()
{
	float curr_time = static_cast<float>(glfwGetTime());
	x_delta_time = curr_time - x_last_time;
	x_last_time = curr_time;
}

const float Time::getDeltaTime()
{
	return x_delta_time;
}

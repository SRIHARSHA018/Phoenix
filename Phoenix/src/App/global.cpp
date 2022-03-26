#include "global.h"

float Time::lastTime = 0.f;
float Time::deltaTime = 0.f;

void Time::updateDeltaTime()
{
	float currTime = static_cast<float>(glfwGetTime());
	deltaTime = currTime - lastTime;
	lastTime = currTime;
}

const float Time::getDeltaTime()
{
	return deltaTime;
}

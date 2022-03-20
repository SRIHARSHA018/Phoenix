#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>



class Time
{
private:
    static float lastTime;
    static float deltaTime;
    ~Time() {}
private:
    Time() {}
public:
    static void updateDeltaTime();
    static const float getDeltaTime();
};




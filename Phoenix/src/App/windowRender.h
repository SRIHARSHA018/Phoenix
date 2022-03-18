#pragma once
#include<GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Events/WindowEvents.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

struct windowProperties
{
    unsigned int  mainWindowWidth = 1280;
    unsigned int  mainWindowHeight = 720;
    std::string mainWindowTitle = "Phoenix";
    eventCallbackFunc eventCallback;
};

class windowRender
{
public:
    windowRender();
    ~windowRender();

public:
    void shutDown();
    void setWindowProperties(windowProperties props);
    void setWindowProperties(unsigned int width, unsigned int height);
    GLFWwindow *getMainWindow() { return this->x_mainWindow; }
    windowProperties getWindowProperties() { return winProps; }
    void setEventCallback(const eventCallbackFunc&  func);
    windowProperties winProps;
    static float getAspectRatio(GLFWwindow* window);
private:
    void x_init();
    

private:
    GLFWwindow *x_mainWindow;
};
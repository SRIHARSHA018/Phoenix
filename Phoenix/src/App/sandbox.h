#pragma once
#include"Events/Event.h"

#include<GLEW/glew.h>
#include <GLFW/glfw3.h>

class InputControls;
class windowRender;
class Renderer;
class sandBox
{
    sandBox() {}
public:

    sandBox &operator=(const sandBox &) = delete;
    sandBox(const sandBox &) = delete;

    ~sandBox();
public:
    void init();
    void onEvent(IEvent& e);
    void run();
    
    GLFWwindow* getWindow();

    static sandBox* getSandBox();

private:
    windowRender *x_windowRender;
    Renderer *x_renderer;
    InputControls* x_inputController;
    static sandBox* x_sanbox;

private:
    void x_setupWindowRender();
    void x_setupRenderer();
    void x_setupInputController();
};
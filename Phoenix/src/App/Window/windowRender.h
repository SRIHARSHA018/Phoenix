#pragma once
#include<GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "WindowUtils.h"

class Window
{
public:
	~Window();

public:
	void shutDown();

	void setWindowProperties(windowProperties props);
	void setWindowProperties(unsigned int width, unsigned int height);

	void setEventCallback(const eventCallbackFunc& func);

	static std::shared_ptr<Window>& get();
	static float getAspectRatio(GLFWwindow* window);

	GLFWwindow* getMainWindow() { return this->x_mainWindow; }
	windowProperties winProps;

private:
	void x_init();

private:
	GLFWwindow* x_mainWindow;
	static std::shared_ptr<Window> x_instance;

private:
	Window();
};
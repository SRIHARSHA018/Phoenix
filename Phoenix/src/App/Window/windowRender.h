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

	void setWindowProperties(WindowProperties props);
	void setWindowProperties(unsigned int width, unsigned int height);

	void setEventCallback(const EventCallbackFunc& func);

	static std::shared_ptr<Window>& get();
	static float getAspectRatio(GLFWwindow* window);

	GLFWwindow* getMainWindow() { return this->x_main_window; }
	WindowProperties win_props;

private:
	void x_init();

private:
	GLFWwindow* x_main_window;
	static std::shared_ptr<Window> x_instance;

private:
	Window();
};
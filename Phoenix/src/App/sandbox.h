#pragma once
#include<GLEW/glew.h>
#include <GLFW/glfw3.h>
#include<memory>

#include "Window/windowRender.h"
#include "InputControls.h"
#include "renderer.h"

class sandBox
{
	sandBox() {}
public:

	sandBox& operator=(const sandBox&) = delete;
	sandBox(const sandBox&) = delete;

	~sandBox();
public:
	void init();
	void onEvent(IEvent& e);
	void run();

	static std::shared_ptr<sandBox>& get();

	GLFWwindow* getWindow();

private:
	std::shared_ptr<Window> x_windowRender;
	std::unique_ptr<InputControls> x_inputController;
	std::unique_ptr<Renderer> x_renderer;

	static std::shared_ptr<sandBox> x_instance;

private:
	void x_setupWindowRender();
	void x_setupRenderer();
	void x_setupInputController();
};
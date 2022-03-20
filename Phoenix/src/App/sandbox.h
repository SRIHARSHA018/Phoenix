#pragma once
#include<GLEW/glew.h>
#include <GLFW/glfw3.h>
#include<memory>

#include "windowRender.h"
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

	GLFWwindow* getWindow();
	static std::shared_ptr<sandBox>& getSandBox();

private:

	std::unique_ptr<InputControls> x_inputController;
	std::unique_ptr<Renderer> x_renderer;
	std::unique_ptr<windowRender> x_windowRender;

	static std::shared_ptr<sandBox> x_sandBox;

private:
	void x_setupWindowRender();
	void x_setupRenderer();
	void x_setupInputController();
};
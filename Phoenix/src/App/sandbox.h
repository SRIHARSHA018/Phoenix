#pragma once
#include<GLEW/glew.h>
#include <GLFW/glfw3.h>
#include<memory>

#include "Window/WindowRender.h"
#include "InputControls.h"
#include "RenderSystem/Renderer.h"

class SandBox
{
	SandBox() {}
public:

	SandBox& operator=(const SandBox&) = delete;
	SandBox(const SandBox&) = delete;

	~SandBox();
public:
	void init();
	void onEvent(IEvent& e);
	void run();

	static std::shared_ptr<SandBox>& get();

	GLFWwindow* getWindow();

private:
	std::shared_ptr<Window> x_window_render;
	std::unique_ptr<InputControls> x_input_controller;
	std::unique_ptr<Renderer> x_renderer;
	static std::shared_ptr<SandBox> x_instance;

private:
	void x_setupWindowRender();
	void x_setupRenderer();
	void x_setupInputController();
};
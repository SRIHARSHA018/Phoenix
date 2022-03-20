#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

class InputControls
{
public:
	InputControls(GLFWwindow* win);

public:
	static bool isKeyPressed(int keyCode);
	static bool isKeyReleased(int keyCode);
	static glm::vec2 getCursorPos();
	static GLFWwindow* window;
	static bool  isMouseButtonClicked(int keyCode);
	static bool  isMouseButtonReleased(int keyCode);
};
#include "InputControls.h"



GLFWwindow* InputControls::window = nullptr;


InputControls::InputControls(GLFWwindow* win)
{
	window = win;
}

bool InputControls::isKeyPressed(int keyCode)
{
	auto state = glfwGetKey(window, keyCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}
bool InputControls::isKeyReleased(int keyCode)
{
	auto state = glfwGetKey(window, keyCode);
	return state == GLFW_RELEASE;
}

glm::vec2 InputControls::getCursorPos()
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
}

bool InputControls::isMouseButtonClicked(int keyCode)
{
	auto state = glfwGetMouseButton(window, keyCode);
	return state == GLFW_PRESS;
}
bool InputControls::isMouseButtonReleased(int keyCode)
{
	auto state = glfwGetMouseButton(window, keyCode);
	return state == GLFW_RELEASE;
}

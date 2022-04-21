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
	double x_pos, y_pos;
	glfwGetCursorPos(window, &x_pos, &y_pos);
	return glm::vec2(static_cast<float>(x_pos), static_cast<float>(y_pos));
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

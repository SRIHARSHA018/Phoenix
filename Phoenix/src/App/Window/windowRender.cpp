#include "windowRender.h"
#include "vertexBuffers/vertexbuffer.h"

void errorCallback(int errorCode, const char* description)
{
	std::cout << errorCode << ":" << description << "\n";
}

std::shared_ptr<Window> Window::x_instance = NULL;

Window::Window()
{
	this->x_init();
}

Window::~Window()
{
	shutDown();
}

void Window::x_init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->x_mainWindow = glfwCreateWindow(winProps.mainWindowWidth,
		winProps.mainWindowHeight,
		winProps.mainWindowTitle.c_str(),
		nullptr, nullptr);

	if (this->x_mainWindow == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		shutDown();
	}
	else
	{
		glfwMakeContextCurrent(this->x_mainWindow);
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
			shutDown();
		}
		glfwSetErrorCallback(errorCallback);
		glfwSetWindowUserPointer(this->x_mainWindow, this);

		// TODO: refine resize callback 
		glfwSetFramebufferSizeCallback(this->x_mainWindow, [](GLFWwindow* window, int width, int height) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));
			windowUserPointer->setWindowProperties(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
			glViewport(0, 0, static_cast<unsigned int>(width), static_cast<unsigned int>(height));
			WindowResizeEvent event(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
			windowUserPointer->winProps.eventCallback(event);
			});
		glfwSetWindowCloseCallback(this->x_mainWindow, [](GLFWwindow* window) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			windowUserPointer->winProps.eventCallback(event);
			});
		glfwSetKeyCallback(this->x_mainWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				keyPressedEvent event(key, 0);
				windowUserPointer->winProps.eventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				keyReleasedEvent event(key);
				windowUserPointer->winProps.eventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				keyPressedEvent event(key, 1);
				windowUserPointer->winProps.eventCallback(event);
				break;
			}
			default:
				break;
			}
			});
		glfwSetCursorPosCallback(this->x_mainWindow, [](GLFWwindow* window, double xpos, double ypos) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));
			MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
			windowUserPointer->winProps.eventCallback(event);
			});
		glfwSetMouseButtonCallback(this->x_mainWindow, [](GLFWwindow* window, int button, int action, int mods) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonClickedEvent event(button);
				windowUserPointer->winProps.eventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				windowUserPointer->winProps.eventCallback(event);
				break;
			}
			}
			});
		glfwSetScrollCallback(this->x_mainWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));
			MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
			windowUserPointer->winProps.eventCallback(event);
			});

	}
}

void Window::setWindowProperties(windowProperties props)
{
	winProps.mainWindowWidth = props.mainWindowWidth;
	winProps.mainWindowHeight = props.mainWindowHeight;
	winProps.mainWindowTitle = props.mainWindowTitle;
}
void Window::setWindowProperties(unsigned int width, unsigned int height)
{
	winProps.mainWindowWidth = width;
	winProps.mainWindowHeight = height;
}
void Window::setEventCallback(const eventCallbackFunc& func)
{
	winProps.eventCallback = func;
}
std::shared_ptr<Window>& Window::get()
{
	if (x_instance != NULL) return x_instance;
	x_instance = std::shared_ptr<Window>(new Window());
	return x_instance;
}
float Window::getAspectRatio(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return (float)width / (float)height;
}
void Window::shutDown()
{
	glfwDestroyWindow(this->x_mainWindow);
	glfwTerminate();
}
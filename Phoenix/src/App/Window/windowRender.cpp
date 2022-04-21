#include "WindowRender.h"
#include "VertexBuffers/Vertexbuffer.h"

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

	this->x_main_window = glfwCreateWindow(win_props.main_window_width,
		win_props.main_window_height,
		win_props.main_window_title.c_str(),
		nullptr, nullptr);

	if (this->x_main_window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		shutDown();
	}
	else
	{
		glfwMakeContextCurrent(this->x_main_window);
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
			shutDown();
		}
		glfwSetErrorCallback(errorCallback);
		glfwSetWindowUserPointer(this->x_main_window, this);

		// TODO: refine resize callback 
		glfwSetFramebufferSizeCallback(this->x_main_window, [](GLFWwindow* window, int width, int height) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));
			windowUserPointer->setWindowProperties(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
			glViewport(0, 0, static_cast<unsigned int>(width), static_cast<unsigned int>(height));
			WindowResizeEvent event(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
			windowUserPointer->win_props.event_callback(event);
			});
		glfwSetWindowCloseCallback(this->x_main_window, [](GLFWwindow* window) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			windowUserPointer->win_props.event_callback(event);
			});
		glfwSetKeyCallback(this->x_main_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				windowUserPointer->win_props.event_callback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				windowUserPointer->win_props.event_callback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				windowUserPointer->win_props.event_callback(event);
				break;
			}
			default:
				break;
			}
			});
		glfwSetCursorPosCallback(this->x_main_window, [](GLFWwindow* window, double xpos, double ypos) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));
			MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
			windowUserPointer->win_props.event_callback(event);
			});
		glfwSetMouseButtonCallback(this->x_main_window, [](GLFWwindow* window, int button, int action, int mods) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonClickedEvent event(button);
				windowUserPointer->win_props.event_callback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				windowUserPointer->win_props.event_callback(event);
				break;
			}
			}
			});
		glfwSetScrollCallback(this->x_main_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			auto windowUserPointer = (Window*)(glfwGetWindowUserPointer(window));
			MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
			windowUserPointer->win_props.event_callback(event);
			});

	}
}

void Window::setWindowProperties(WindowProperties props)
{
	win_props.main_window_width = props.main_window_width;
	win_props.main_window_height = props.main_window_height;
	win_props.main_window_title = props.main_window_title;
}
void Window::setWindowProperties(unsigned int width, unsigned int height)
{
	win_props.main_window_width = width;
	win_props.main_window_height = height;
}
void Window::setEventCallback(const EventCallbackFunc& func)
{
	win_props.event_callback = func;
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
	glfwDestroyWindow(this->x_main_window);
	glfwTerminate();
}
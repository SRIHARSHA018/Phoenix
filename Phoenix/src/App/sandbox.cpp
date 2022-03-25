#include "sandbox.h"

std::shared_ptr<sandBox> sandBox::x_sandBox = NULL;

void sandBox::init()
{
	this->x_setupWindowRender();

	this->x_setupRenderer();

	this->x_setupInputController();

}
void sandBox::run()
{
	this->x_renderer->run(this->x_windowRender->getMainWindow());
}

GLFWwindow* sandBox::getWindow()
{
	return this->x_windowRender->getMainWindow();
}

std::shared_ptr<sandBox>& sandBox::getSandBox()
{
	if (x_sandBox != NULL) return x_sandBox;
	x_sandBox = std::shared_ptr<sandBox>(new sandBox());
	return x_sandBox;
}

void sandBox::x_setupWindowRender()
{
	this->x_windowRender = std::unique_ptr<windowRender>(new windowRender());
	this->x_windowRender->setEventCallback(std::bind(&sandBox::onEvent, this, std::placeholders::_1));
}
void sandBox::x_setupRenderer()
{
	this->x_renderer = std::unique_ptr<Renderer>(new Renderer());
}
void sandBox::x_setupInputController()
{
	if (this->x_windowRender != NULL) {
		this->x_inputController = std::unique_ptr<InputControls>(new InputControls(this->x_windowRender->getMainWindow()));
	}
}

void sandBox::onEvent(IEvent& e)
{
	//switch (e.getEventType())
	//{
	//case EventType::WINDOW_RESIZE:
	//    std::cout << "window resize Event\n";
	//    break;
	//case EventType::WINDOW_CLOSE:
	//    std::cout << "Window close Event\n";
	//    break;
	//case EventType::KEY_PRESSED:
	//    std::cout << "key pressed Event\n";
	//    if (InputControls::isKeyPressed(GLFW_KEY_ESCAPE)) {
	//        glfwSetWindowShouldClose(this->x_windowRender->getMainWindow(), true);
	//    }
	//    break;
	//case EventType::KEY_REPEAT:
	//    std::cout << "key Repeat Event\n";
	//    break;
	//case EventType::KEY_RELEASED:
	//    std::cout << "key released Event\n";
	//    break;
	//case EventType::MOUSE_MOVED:
	//    std::cout << "Mouse Moved Event\n";
	//    break;
	//case EventType::MOUSE_BUTTON_CLICKED:
	//    std::cout << "Mouse Button clicked Event\n";
	//    break;
	//case EventType::MOUSE_BUTTON_RELEASED:
	//    std::cout << "Mouse Button Released Event\n";
	//    break;
	//case EventType::MOUSE_SCROLLED:
	//    std::cout << "Mouse Scrolled Event\n";
	//    break;
	//default:
	//    break;
	//}
	this->x_renderer->onEvent(e);

}

sandBox::~sandBox()
{
}
#include "sandbox.h"

std::shared_ptr<SandBox> SandBox::x_instance = NULL;

void SandBox::init()
{
	this->x_setupWindowRender();

	this->x_setupRenderer();

	this->x_setupInputController();

}
void SandBox::run()
{
	this->x_renderer->run(this->x_window_render->getMainWindow());
}

GLFWwindow* SandBox::getWindow()
{
	return this->x_window_render->getMainWindow();
}

std::shared_ptr<SandBox>& SandBox::get()
{
	if (x_instance != NULL) return x_instance;
	x_instance = std::shared_ptr<SandBox>(new SandBox());
	return x_instance;
}

void SandBox::x_setupWindowRender()
{
	this->x_window_render = Window::get();
	this->x_window_render->setEventCallback(std::bind(&SandBox::onEvent, this, std::placeholders::_1));
}
void SandBox::x_setupRenderer()
{
	this->x_renderer = std::unique_ptr<Renderer>(new Renderer());
}
void SandBox::x_setupInputController()
{
	if (this->x_window_render != NULL) {
		this->x_input_controller = std::unique_ptr<InputControls>(new InputControls(this->x_window_render->getMainWindow()));
	}
}

void SandBox::onEvent(IEvent& e)
{
	this->x_renderer->onEvent(e);
}

SandBox::~SandBox()
{
}
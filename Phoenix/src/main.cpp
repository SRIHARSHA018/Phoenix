#include<memory>

#include "App/sandbox.h"

int main()
{
	std::shared_ptr<sandBox> phoenixSandbox = sandBox::getSandBox();
	phoenixSandbox->init();
	phoenixSandbox->run();
}
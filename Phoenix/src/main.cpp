#include<memory>
#include "App/Sandbox.h"
#include "ECS/Entity.h"


int main()
{
	std::shared_ptr<SandBox> phoenix_sandbox = SandBox::get();
	phoenix_sandbox->init();
	phoenix_sandbox->run();
}
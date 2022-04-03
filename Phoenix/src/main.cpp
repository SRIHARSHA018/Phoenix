#include<memory>

#include "App/sandbox.h"
#include "ECS/Entity.h"

struct Name {
	std::string name;
};
int main()
{
	std::vector<Entity> entities;
	for (unsigned int i = 0; i < 1000; i++) {
		Entity entity;
		entity.attachComponent<Name>();
		entity.getComponent<Name>().name = "book" + std::to_string(i);
		std::cout << entity.getComponent<Name>().name << std::endl;
		entities.emplace_back(entity);
	}

	//std::shared_ptr<sandBox> phoenixSandbox = sandBox::get();
	//phoenixSandbox->init();
	//phoenixSandbox->run();
}
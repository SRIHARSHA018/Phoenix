#include<memory>

#include "App/sandbox.h"
#include "ECS/Entity.h"


int main()
{

	//ECS testing 
	struct Name {
		std::string name;
	};
	struct Category {
		std::string name = "Default";
	};
	std::vector<Entity> entities;
	for (unsigned int i = 0; i < 1000; i++) {
		Entity entity;
		entity.attachComponent<Name>();
		entity.attachComponent<Category>();
		entity.getComponent<Name>().name = "book" + std::to_string(i);
		std::cout << entity.getComponent<Name>().name << std::endl;
		entities.emplace_back(entity);
	}
	entities[0].detachComponent<Name>();
	std::cout << entities[0].getComponent<Category>().name << "\n";


	//std::shared_ptr<sandBox> phoenixSandbox = sandBox::get();
	//phoenixSandbox->init();
	//phoenixSandbox->run();
}
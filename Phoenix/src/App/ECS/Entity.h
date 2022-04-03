#pragma once

#include "Component.h"

class Entity {
public:
	Entity() {
		EntityIdCounter += 1;
		id = EntityIdCounter;
		x_componentContainers.resize(MAX_COMPONENTS);
		x_componentContainers.shrink_to_fit();
	}
	~Entity() {
		this->x_mask.reset();
		this->x_componentContainers.clear();
		this->x_componentContainers.shrink_to_fit();
	}

public:
	EntityId id;

	template<typename T>
	void attachComponent() {
		x_mask.set(getComponentTypeID<T>(), true);
		x_componentContainers[getComponentTypeID<T>()] = std::make_shared<Component<T>>();
	}

	template<typename T>
	void detachComponent() {
		x_componentContainers[getComponentTypeID<T>()].reset();
		x_mask.set(getComponentTypeID<T>(), false);
	}

	template<typename T>
	bool hasComponent() {
		return x_mask.test(getComponentTypeID<T>());
	}

	template<typename T>
	T& getComponent() {
		ComponentTypeId index = -1;
		if (hasComponent<T>()) {
			index = getComponentTypeID<T>();
		}
		return (std::static_pointer_cast<Component<T>>(x_componentContainers[index]))->component;
	}

private:
	static EntityId EntityIdCounter;

private:
	ComponentMask x_mask;
	std::vector<std::shared_ptr<IComponentContainer>> x_componentContainers;
};
EntityId Entity::EntityIdCounter = 0;
#pragma once

#include "Component.h"

class Entity {
public:
	Entity() {
		entity_id_counter += 1;
		id = entity_id_counter;
		x_component_containers.resize(MAX_COMPONENTS);
		x_component_containers.shrink_to_fit();
	}
	~Entity() {
		this->x_mask.reset();
		this->x_component_containers.clear();
		this->x_component_containers.shrink_to_fit();
	}

public:
	EntityId id;

	template<typename T>
	void attachComponent() {
		x_mask.set(getComponentTypeID<T>(), true);
		x_component_containers[getComponentTypeID<T>()] = std::make_shared<Component<T>>();
	}

	template<typename T>
	void detachComponent() {
		x_component_containers[getComponentTypeID<T>()].reset();
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
		return (std::static_pointer_cast<Component<T>>(x_component_containers[index]))->component;
	}

private:
	static EntityId entity_id_counter;

private:
	ComponentMask x_mask;
	std::vector<std::shared_ptr<IComponentContainer>> x_component_containers;
};
EntityId Entity::entity_id_counter = 0;
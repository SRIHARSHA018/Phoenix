#pragma once

#include "Component.h"

class Entity {
public:
	Entity() {
		EntityIdCounter += 1;
		id = EntityIdCounter;
		x_componentContainers.resize(MAX_COMPONENTS);
	}
	~Entity() {
		this->x_mask.reset();
		this->x_componentContainers.clear();
		this->x_componentContainers.shrink_to_fit();
		this->x_typeToComponentTypeId.clear();
	}

public:
	EntityId id;

	template<typename T>
	void attachComponent() {
		const char* type = typeid(T).name();
		if (x_typeToComponentTypeId.find(type) == x_typeToComponentTypeId.end()) {
			x_typeToComponentTypeId[type] = getUniqueComponentId();
			x_mask.set(x_typeToComponentTypeId[type], true);
			x_componentContainers[x_typeToComponentTypeId[type]] = std::make_shared<Component<T>>();
		}
		else {
			std::cout << "Component already attached\n";
		}
	}

	template<typename T>
	void detachComponent() {
		const char* type = typeid(T).name();
		if (x_typeToComponentTypeId.find(type) != x_typeToComponentTypeId.end()) {
			x_typeToComponentTypeId.erase(type);
			x_mask.set(x_typeToComponentTypeId[type], false);
		}
		else {
			std::cout << "Component already Detached\n";
		}
	}

	template<typename T>
	bool hasComponent() {
		if (x_hasComponent<T>()) {
			return true;
		}
		std::cout << "Component is not present\n";
		return false;
	}

	template<typename T>
	T& getComponent() {
		ComponentTypeId index;
		if (hasComponent<T>()) {
			index = x_typeToComponentTypeId[typeid(T).name()];
		}
		return (std::static_pointer_cast<Component<T>>(x_componentContainers[index]))->component;
	}

private:
	static EntityId EntityIdCounter;

private:
	ComponentMask x_mask;
	std::vector<std::shared_ptr<IComponentContainer>> x_componentContainers;
	std::unordered_map<const char*, ComponentTypeId> x_typeToComponentTypeId;

private:
	template<typename T>
	bool x_hasComponent() {
		const char* type = typeid(T).name();
		return (x_typeToComponentTypeId.find(type) != x_typeToComponentTypeId.end()) && (x_mask.test(x_typeToComponentTypeId[type]));
	}
};
EntityId Entity::EntityIdCounter = 0;
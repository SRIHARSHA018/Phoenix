#pragma once
#include "ecs.h"

class IComponentContainer {
public:
	virtual ~IComponentContainer() = default;
};

template<typename T>
class Component : public IComponentContainer {
public:
	Component() = default;
	T component;
};

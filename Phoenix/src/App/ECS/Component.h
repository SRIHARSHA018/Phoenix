#pragma once
#include "ECS.h"

class IComponentContainer {
public:
	virtual ~IComponentContainer() = default;
};

template<typename T>
struct Component : public IComponentContainer {
	T component;
};

#pragma once
#include<bitset>
#include<memory>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<queue>

#define MAX_COMPONENTS 32

using EntityId = unsigned long long;
using ComponentTypeId = unsigned long long;
using ComponentMask = std::bitset<MAX_COMPONENTS>;

ComponentTypeId getUniqueComponentId() {
	static ComponentTypeId lastId = 0u;
	return lastId++;
}


template<typename T>
ComponentTypeId getComponentTypeID() noexcept {
	static const ComponentTypeId typeId = getUniqueComponentId();
	return typeId;
}
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
	static ComponentTypeId last_id = 0u;
	return last_id++;
}


template<typename T>
ComponentTypeId getComponentTypeID() noexcept {
	static const ComponentTypeId type_id = getUniqueComponentId();
	return type_id;
}
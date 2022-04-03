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

#pragma once

class ISystem {
public:
	virtual ~ISystem() = default;
	virtual void update() = 0;
};
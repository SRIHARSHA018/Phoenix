#pragma once
#include <string>
#include <iostream>
#include <memory>

#include "Events/WindowEvents.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"


struct windowProperties
{
	unsigned int  mainWindowWidth = 1280;
	unsigned int  mainWindowHeight = 720;
	std::string mainWindowTitle = "Phoenix";
	eventCallbackFunc eventCallback;
};


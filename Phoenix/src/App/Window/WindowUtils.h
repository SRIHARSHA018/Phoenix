#pragma once
#include <string>
#include <iostream>
#include <memory>

#include "Events/WindowEvents.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"


struct WindowProperties
{
	unsigned int  main_window_width = 1280;
	unsigned int  main_window_height = 720;
	std::string main_window_title = "Phoenix";
	EventCallbackFunc event_callback;
};


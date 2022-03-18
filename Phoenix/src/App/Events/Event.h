#pragma once
#include<functional>

enum class EventType
{
	WINDOW_RESIZE,
	WINDOW_CLOSE,
	KEY_PRESSED,KEY_RELEASED,KEY_REPEAT,
	MOUSE_MOVED,MOUSE_BUTTON_CLICKED, MOUSE_BUTTON_RELEASED,MOUSE_SCROLLED,MOUSE_HOVERED
};

class IEvent
{
public:
	virtual ~IEvent() = default;

	virtual EventType getEventType() const = 0;

};
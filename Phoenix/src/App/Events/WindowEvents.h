#pragma once
#include "Event.h"



using EventCallbackFunc = std::function<void(IEvent&)>;
class WindowResizeEvent : public IEvent
{
public:
	WindowResizeEvent(unsigned int width, unsigned int height) :x_width(width), x_height(height) {}
	~WindowResizeEvent() {}

	virtual EventType getEventType() const override {
		return EventType::WINDOW_RESIZE;
	}

	unsigned int getWidth() { return x_width; }
	unsigned int getHeight() { return x_height; }

private:
	unsigned int x_width;
	unsigned int x_height;
};

class WindowCloseEvent :public IEvent
{
public:
	WindowCloseEvent() = default;
	~WindowCloseEvent() {}
	virtual EventType getEventType() const override {
		return EventType::WINDOW_CLOSE;
	}
};
#pragma once
#include "Event.h"

class MouseMovedEvent :public IEvent
{
public:
	MouseMovedEvent(float xpos, float ypos) :x_xpos(xpos), x_ypos(ypos) {}
	virtual EventType getEventType() const override {
		return EventType::MOUSE_MOVED;
	}
	float GetCursorX() { return x_xpos; }
	float GetCursorY() { return x_ypos; }
private:
	float x_xpos, x_ypos;
};

class MouseButtonClickedEvent :public IEvent
{
public:
	MouseButtonClickedEvent(unsigned int key_code) :x_key_code(key_code) {}
	virtual EventType getEventType() const override {
		return EventType::MOUSE_BUTTON_CLICKED;
	}
	unsigned int getKeyCode() { return x_key_code; }
private:
	unsigned int x_key_code;
};

class MouseButtonReleasedEvent :public IEvent
{
public:
	MouseButtonReleasedEvent(unsigned int key_code) :x_key_code(key_code) {}
	virtual EventType getEventType() const override {
		return EventType::MOUSE_BUTTON_RELEASED;
	}
	unsigned int getKeyCode() { return x_key_code; }
private:
	unsigned int x_key_code;
};

class MouseScrolledEvent :public IEvent
{
public:
	MouseScrolledEvent(float xoff, float yoff) :x_xoff(xoff), x_yoff(yoff) {}

	virtual EventType getEventType()const override {
		return EventType::MOUSE_SCROLLED;
	}
	float getXoffset() { return x_xoff; }
	float getYoffset() { return x_yoff; }

private:
	float x_xoff, x_yoff;
};
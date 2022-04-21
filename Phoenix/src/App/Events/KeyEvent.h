#pragma once

#include "Event.h"


class KeyPressedEvent :public IEvent
{
public:
	KeyPressedEvent(const unsigned int key_code, const unsigned int repeat_count) :x_key_code(key_code), x_repeat_count(repeat_count) {}
	EventType getEventType() const  override { return EventType::KEY_PRESSED; }
	unsigned int getKeyCode() const { return x_key_code; }
	unsigned int getRepeatCount() const { return x_repeat_count; }
private:
	unsigned int x_key_code, x_repeat_count;
};

class KeyReleasedEvent :public IEvent
{
public:
	KeyReleasedEvent(const unsigned int key_code) :x_key_code(key_code) {}
	EventType getEventType() const override { return EventType::KEY_RELEASED; }
	unsigned int getKeyCode() const { return x_key_code; }
private:
	unsigned int x_key_code;
};

#pragma once

#include "Event.h"


class keyPressedEvent:public IEvent
{
public:
	keyPressedEvent(const unsigned int keyCode,const unsigned int repeatCount) :x_keyCode(keyCode),x_repeatCount(repeatCount) {}
	EventType getEventType() const  override { return EventType::KEY_PRESSED; }
	unsigned int getKeyCode() const { return x_keyCode; }
	unsigned int getRepeatCount() const { return x_repeatCount; }
private:
	unsigned int x_keyCode,x_repeatCount;
};

class keyReleasedEvent :public IEvent
{
public:
	keyReleasedEvent(const unsigned int keyCode) :x_keyCode(keyCode) {}
	EventType getEventType() const override { return EventType::KEY_RELEASED; }
	unsigned int getKeyCode() const { return x_keyCode; }
private:
	unsigned int x_keyCode;
};

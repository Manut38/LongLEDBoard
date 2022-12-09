#pragma once
#include "FastLED.h"
#include "Config.h"

class LedEffect
{
protected:
	u_long timer;
	int timerDelay;
	virtual void timedLoop() = 0;

public:
	CRGB mask[NUM_LEDS];
	bool remove = false;

	virtual void loop();
};
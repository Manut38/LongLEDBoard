#include "LedEffect/EffectBlink.h"

EffectBlink::EffectBlink(int delay, CRGB color)
{
	this->timerDelay = delay;
	this->color = color;
	blinkIsOn = false;
}

void EffectBlink::timedLoop()
{
	if (!blinkIsOn)
	{
		fill_solid(mask, NUM_LEDS, color);
		blinkIsOn = true;
	}
	else
	{
		fill_solid(mask, NUM_LEDS, CRGB::Black);
		blinkIsOn = false;
	}
}
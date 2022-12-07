#include "BlinkEffect.h"

BlinkEffect::BlinkEffect(int delay, CRGB color)
{
	this->timerDelay = delay;
	this->color = color;
	blinkIsOn = false;
}

void BlinkEffect::timedLoop()
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
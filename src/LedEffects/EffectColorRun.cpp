#include "LedEffect/EffectColorRun.h"

EffectColorRun::EffectColorRun(int duration, CRGB color, bool invert)
{
	fill_solid(mask, NUM_LEDS, CRGB::Black);

	this->timerDelay = duration / NUM_LEDS / 2;
	this->color = color;
	this->invert = invert;
	resetCurrentLed();
	reverse = false;
}

void EffectColorRun::resetCurrentLed()
{
	currentLed = invert ? NUM_LEDS - 1 : 0;
}

void EffectColorRun::timedLoop()
{
	if (!reverse)
	{
		mask[currentLed] = color;
	}
	else
	{
		mask[currentLed] = CRGB::Black;
	}
	currentLed = invert ? currentLed - 1 : currentLed + 1;
	if ((invert && currentLed <= 0) || !invert && currentLed >= NUM_LEDS)
	{
		if (!reverse)
		{
			reverse = true;
			resetCurrentLed();
		}
		else
		{
			remove = true;
		}
	}
}
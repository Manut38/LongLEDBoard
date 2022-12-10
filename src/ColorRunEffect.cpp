#include "ColorRunEffect.h"

ColorRunEffect::ColorRunEffect(int duration, CRGB color, bool invert)
{
	fill_solid(mask, NUM_LEDS, CRGB::Black);

	int timerDelay = duration / NUM_LEDS / 2;
	if (timerDelay <= 0)
		timerDelay = 1;
	this->timerDelay = timerDelay;
	this->color = color;
	this->invert = invert;
	resetCurrentLed();
	reverse = false;
}

void ColorRunEffect::resetCurrentLed()
{
	currentLed = invert ? NUM_LEDS - 1 : 0;
}

void ColorRunEffect::timedLoop()
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
	if (invert && currentLed <= 0 || !invert && currentLed >= NUM_LEDS)
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
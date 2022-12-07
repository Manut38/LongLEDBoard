#include "ColorRunEffect.h"

ColorRunEffect::ColorRunEffect(int delay, CRGB color)
{
	fill_solid(mask, NUM_LEDS, CRGB::Black);

	this->timerDelay = delay;
	this->color = color;
	colorRunCurrentLed = 0;
	colorRunReverse = false;
}

void ColorRunEffect::timedLoop()
{
	if (!colorRunReverse)
	{
		mask[colorRunCurrentLed++] = color;
	}
	else
	{
		mask[colorRunCurrentLed++] = CRGB::Black;
	}
	if (colorRunCurrentLed >= NUM_LEDS)
	{
		if (!colorRunReverse)
		{
			colorRunReverse = true;
			colorRunCurrentLed = 0;
		}
		else
		{
			remove = true;
		}
	}
}
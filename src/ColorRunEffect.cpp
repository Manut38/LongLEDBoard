#include "ColorRunEffect.h"

ColorRunEffect::ColorRunEffect(int duration, CRGB color)
{
	fill_solid(mask, NUM_LEDS, CRGB::Black);

	int timerDelay = duration / NUM_LEDS / 2;
	if (timerDelay <= 0)
		timerDelay = 1;
	this->timerDelay = timerDelay;
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
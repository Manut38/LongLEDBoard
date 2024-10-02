#include "LedEffect/EffectRainbowStrike.h"

EffectRainbowStrike::EffectRainbowStrike(int duration, bool invert)
{
	fill_rainbow(rainbowMask, NUM_LEDS, 0, 7);
	this->timerDelay = duration / NUM_LEDS / 2 / 2;
	this->invert = invert;
	resetCurrentLed();
	reverse = false;
}

EffectRainbowStrike::EffectRainbowStrike(LedEffectConfig *effectConfig)
	: EffectRainbowStrike(
		  effectConfig->accelEffect.rainbowStrike.duration,
		  false) {}

void EffectRainbowStrike::resetCurrentLed()
{
	currentLed = invert ? NUM_LEDS - 1 : 0;
}

void EffectRainbowStrike::timedLoop()
{
	if (!reverse)
	{
		mask[currentLed] = rainbowMask[currentLed];
	}
	else
	{
		mask[currentLed] = CRGB::Black;
	}
	currentLed = invert ? currentLed - 1 : currentLed + 1;
	if ((invert && currentLed <= 0) || (!invert && (currentLed >= NUM_LEDS)))
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

#include "LedEffect/EffectSolidColor.h"

EffectSolidColor::EffectSolidColor(CRGB color) : color(color)
{
	fill_solid(mask, NUM_LEDS, color);
}

void EffectSolidColor::timedLoop() {}
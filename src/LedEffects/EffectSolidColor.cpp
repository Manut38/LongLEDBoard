#include "LedEffect/EffectSolidColor.h"

EffectSolidColor::EffectSolidColor(CRGB color) : color(color)
{
	fill_solid(mask, NUM_LEDS, color);
}

EffectSolidColor::EffectSolidColor(LedEffectConfig *effectConfig)
	: EffectSolidColor(effectConfig->bgEffect.solidColor.color) {}

void EffectSolidColor::timedLoop() {}

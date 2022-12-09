#include "LED.h"
#include "BlinkEffect.h"
#include "ColorRunEffect.h"

void LED::setup()
{
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(100);
	FastLED.clear();
}

void LED::loop()
{
	// Handle background effect
	if (bgEffectActive)
	{
		bgEffect->loop();

		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = bgEffect->mask[i];
		}
	}

	// Handle foreground effects
	for (LedEffect *e : fgEffects)
	{
		e->loop();

		// Copy every pixel from the effect mask is not black
		for (int i = 0; i < NUM_LEDS; i++)
		{
			if (e->mask[i])
			{
				leds[i] = e->mask[i];
			}
		}
	}

	// Remove all foreground effects with "remove" flag
	fgEffects.erase(std::remove_if(fgEffects.begin(),
								   fgEffects.end(),
								   [&](LedEffect *effect) -> bool
								   { return effect->remove; }),
					fgEffects.end());

	FastLED.show();
}

void LED::addFgEffect(LedEffect *effect)
{
	fgEffects.push_back(effect);
}

void LED::setBgEffect(LedEffect *effect)
{
	bgEffect = effect;
	bgEffectActive = true;
}

void LED::clearBgEffect()
{
	bgEffectActive = false;
}

CRGB LED::getRandomColor(CRGB currentColor)
{
	CRGB randomColor;
	switch ((int)random(8))
	{
	case 0:
		randomColor = CRGB::Lime;
		break;
	case 1:
		randomColor = CRGB::ForestGreen;
		break;
	case 2:
		randomColor = CRGB::Red;
		break;
	case 3:
		randomColor = CRGB::OrangeRed;
		break;
	case 4:
		randomColor = CRGB::DarkViolet;
		break;
	case 5:
		randomColor = CRGB::DeepSkyBlue;
		break;
	case 6:
		randomColor = CRGB::Crimson;
		break;
	case 7:
		randomColor = CRGB::Purple;
		break;
	case 8:
		randomColor = CRGB::Gold;
		break;
	default:
		return CRGB::Red;
	}
	if (currentColor == randomColor)
	{
		return getRandomColor();
	}
	else
	{
		return randomColor;
	}
}

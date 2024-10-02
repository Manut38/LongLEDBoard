#include "LED.h"

#include <memory>

void LED::setup()
{
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalPixelString);
	setGlobalBrightness(DEFAULT_BRIGHTNESS);
	FastLED.clear();
}

void LED::loop()
{
	FastLED.clear();

	// Handle background effect

	bgEffect->loop();

	if (bgEffectActive && globalPower)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = bgEffect->mask[i];
		}
	}

	// Handle foreground effects
	for (auto &e : fgEffects)
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
								   [&](unique_ptr<LedEffect> &effect) -> bool
								   { return effect->remove; }),
					fgEffects.end());

	FastLED.show();
}

void LED::fireAccelEffect()
{
	if (accelEffectActive)
	{
		fgEffects.emplace_back(accelEffect->clone());
	}
}

void LED::addFgEffect(LedEffect *effect)
{
	fgEffects.emplace_back(unique_ptr<LedEffect>(effect));
}

void LED::setBgEffect(LedEffect *effect)
{
	bgEffect = unique_ptr<LedEffect>(effect);
}
void LED::setAccelEffect(LedEffect *effect)
{
	accelEffect = unique_ptr<LedEffect>(effect);
}
void LED::setSteeringEffect(LedEffect *effect)
{
	steeringEffect = unique_ptr<LedEffect>(effect);
}

void LED::reloadAccelEffect()
{
	switch (selectedAccelEffect)
	{
	case AccelEffect::ColorStrike:
		setAccelEffect(new EffectColorStrike(&effectConfig));
		break;
	case AccelEffect::RainbowStrike:
		setAccelEffect(new EffectRainbowStrike(&effectConfig));
		break;
	case AccelEffect::GradientStrike:
		break;
	case AccelEffect::ColorChase:
		break;
	case AccelEffect::Strobe:
		break;
	case AccelEffect::RainbowStrobe:
		break;
	default:
		break;
	};
	fireAccelEffect();
}

void LED::reloadBgEffect()
{
	switch (selectedBgEffect)
	{
	case BgEffect::SolidColor:
		setBgEffect(new EffectSolidColor(&effectConfig));
		break;
	case BgEffect::Breathing:
		break;
	case BgEffect::Rainbow:
		setBgEffect(new EffectRainbowLoop(&effectConfig));
		break;
	case BgEffect::Fire:
		break;
	case BgEffect::ColorChase:
		break;
	case BgEffect::ColorFade:
		break;
	case BgEffect::Sparkle:
		break;
	default:
		break;
	}
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

CRGB LED::colorFromHexString(String hex)
{
	hex = hex.substring(1, hex.length());
	uint32_t c;
	std::istringstream(hex.c_str()) >> std::hex >> c;
	return CRGB(c);
}
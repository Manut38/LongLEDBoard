#pragma once

#include <FastLED.h>
#include <vector>
#include <memory>
#include <sstream>
#include "LedEffect/LedEffect.h"
#include "Config.h"

using namespace std;
class LED
{

private:
	CRGB leds[NUM_LEDS];
	vector<unique_ptr<LedEffect>> fgEffects;
	unique_ptr<LedEffect> bgEffect;
	bool bgEffectActive;

public:
	void setup();
	void loop();

	void addFgEffect(LedEffect *e);
	void setBgEffect(LedEffect *e);
	void clearBgEffect();
	void setGlobalBrightness(uint8 b)
	{
		FastLED.setBrightness(b);
	}

	static CRGB getRandomColor(CRGB currentColor = 0);
	static CRGB colorFromHexString(String hex);
};
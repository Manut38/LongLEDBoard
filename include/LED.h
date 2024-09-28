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
	bool globalPower;
	uint8_t brightness;
	bool bgEffectActive;

public:
	void setup();
	void loop();

	void addFgEffect(LedEffect *e);
	void setBgEffect(LedEffect *e);
	void setGlobalBrightness(uint8 b)
	{
		brightness = b;
		if (globalPower)
			FastLED.setBrightness(brightness);
	}
	void setGlobalPower(bool power)
	{
		globalPower = power;
		if (power)
			FastLED.setBrightness(brightness);
		else
			FastLED.setBrightness(0);
	}
	void setBgEffectActive(bool active) { bgEffectActive = active; }

	static CRGB getRandomColor(CRGB currentColor = 0);
	static CRGB colorFromHexString(String hex);
};
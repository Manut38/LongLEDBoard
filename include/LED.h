#pragma once

#include <FastLED.h>
#include <vector>
#include <memory>
#include <sstream>
#include "Config.h"
#include "LedEffect/LedEffect.h"
#include "LedEffect/LedEffectConfig.h"
#include "LedEffect/LedEffectEnum.h"

#include "LedEffect/EffectBlink.h"
#include "LedEffect/EffectColorStrike.h"
#include "LedEffect/EffectRainbowLoop.h"
#include "LedEffect/EffectRainbowStrike.h"
#include "LedEffect/EffectSolidColor.h"

using namespace std;

class LED
{

private:
	CRGB leds[NUM_LEDS];
	bool globalPower = true;
	uint8_t brightness;

	unique_ptr<LedEffect> bgEffect;
	// unique_ptr<LedEffect> steeringEffect;

	bool bgEffectActive = true;
	bool accelEffectActive = true;
	bool steeringEffectActive = true;

	BgEffect selectedBgEffect = BgEffect::SolidColor;
	AccelEffect selectedAccelEffect = AccelEffect::RainbowStrike;
	// SteeringEffect selectedSteeringEffect = SteeringEffect::RainbowStrike;

	vector<unique_ptr<LedEffect>> fgEffects;

public:
	LedEffectConfig effectConfig;

	void setup();
	void loop();

	void addFgEffect(LedEffect *e);

	void setGlobalBrightness(uint8 b)
	{
		brightness = b;
		if (globalPower)
			FastLED.setBrightness(brightness);
	}
	void setGlobalPower(bool power) { globalPower = power; }
	void setBgEffectActive(bool active) { bgEffectActive = active; }
	void setAccelEffectActive(bool active) { accelEffectActive = active; }
	void setSteeringEffectActive(bool active) { steeringEffectActive = active; }

	void selectBgEffect(BgEffect effect)
	{
		selectedBgEffect = effect;
		reloadBgEffect();
	}
	void selectBgEffect(std::string id) { selectBgEffect(BgEffectMap[id]); }
	void selectAccelEffect(std::string id)
	{
		selectedAccelEffect = AccelEffectMap[id];
		fireAccelEffect();
	}
	void selectSteeringEffect(std::string id);

	void reloadBgEffect();
	void fireAccelEffect();

	static CRGB getRandomColor(CRGB currentColor = 0);
	static CRGB colorFromHexString(String hex);
};
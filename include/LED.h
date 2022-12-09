#include <FastLED.h>
#include <vector>
#include <LedEffect.h>
#include "Config.h"

class LED
{

private:
	CRGB leds[NUM_LEDS];
	std::vector<LedEffect *> fgEffects;
	LedEffect *bgEffect;
	bool bgEffectActive;

public:
	void setup();
	void loop();

	void addFgEffect(LedEffect *effect);
	void setBgEffect(LedEffect *effect);
	void clearBgEffect();

	CRGB getRandomColor(CRGB currentColor = 0);
};
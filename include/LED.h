#include <FastLED.h>
#include <vector>
#include <memory>
#include <LedEffect.h>
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

	CRGB getRandomColor(CRGB currentColor = 0);
};
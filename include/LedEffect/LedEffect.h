#pragma once
#include <memory>
#include "FastLED.h"
#include "Config.h"
#include "LedEffectConfig.h"

class LedEffect
{
protected:
	uint32_t timer;
	uint32_t timerDelay;
	virtual void timedLoop() = 0;

public:
	CRGB mask[NUM_LEDS];
	bool remove = false;

	virtual void loop();

	// virtual ~LedEffect() = default;
	virtual std::unique_ptr<LedEffect> clone() const = 0;

};
#pragma once
#include "LedEffect.h"

class EffectRainbowStrike : public LedEffect
{
private:
	CRGB rainbowMask[NUM_LEDS];
	int currentLed;
	bool reverse;
	bool invert;

protected:
	void timedLoop() override;
	void resetCurrentLed();

public:
	EffectRainbowStrike(int duration, bool invert = false);
	EffectRainbowStrike(LedEffectConfig *effectConfig);

	virtual std::unique_ptr<LedEffect> clone() const override
	{
		return std::make_unique<EffectRainbowStrike>(*this);
	}
};
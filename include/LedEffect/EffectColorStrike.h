#pragma once
#include "LedEffect.h"

class EffectColorStrike : public LedEffect
{
private:
	CRGB color;
	int currentLed;
	bool reverse;
	bool invert;

protected:
	void timedLoop() override;
	void resetCurrentLed();

public:
	EffectColorStrike(int duration, CRGB color, bool invert = false);
	EffectColorStrike(LedEffectConfig *effectConfig);

	virtual std::unique_ptr<LedEffect> clone() const override
	{
		return std::make_unique<EffectColorStrike>(*this);
	}
};
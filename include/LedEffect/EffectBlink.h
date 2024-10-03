#pragma once
#include "LedEffect.h"

class EffectBlink : public LedEffect
{
private:
	CRGB color;
	bool blinkIsOn;

protected:
	void timedLoop() override;

public:
	EffectBlink(int delay, CRGB color);
	EffectBlink(LedEffectConfig *effectConfig);
};
#pragma once
#include "LedEffect.h"

class EffectColorRun : public LedEffect
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
	EffectColorRun(int duration, CRGB color, bool invert = false);
};
#pragma once
#include "LedEffect.h"

class EffectSolidColor : public LedEffect
{
private:
	CRGB color;

protected:
	void timedLoop() override;

public:
	EffectSolidColor(CRGB color);
	EffectSolidColor(LedEffectConfig* effectConfig);

	virtual std::unique_ptr<LedEffect> clone() const override
    {
        return std::make_unique<EffectSolidColor>(*this);
    }
};
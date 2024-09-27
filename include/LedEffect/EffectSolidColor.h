#include "LedEffect.h"

class EffectSolidColor : public LedEffect
{
private:
	CRGB color;

protected:
	void timedLoop() override;

public:
	EffectSolidColor(CRGB color);
};
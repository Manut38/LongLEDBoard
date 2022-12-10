#include "LedEffect.h"

class ColorRunEffect : public LedEffect
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
	ColorRunEffect(int duration, CRGB color, bool invert = false);
};
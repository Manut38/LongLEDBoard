#include "LedEffect.h"

class ColorRunEffect : public LedEffect
{
private:
	CRGB color;
	int colorRunCurrentLed;
	bool colorRunReverse;

protected:
	void timedLoop() override;

public:
	ColorRunEffect(int delay, CRGB color);
};
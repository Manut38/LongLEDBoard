#include "LedEffect.h"

class BlinkEffect : public LedEffect
{
private:
	CRGB color;
	bool blinkIsOn;

protected:
	void timedLoop() override;

public:
	BlinkEffect(int delay, CRGB color);
};
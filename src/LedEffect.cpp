#include "LedEffect.h"

void LedEffect::loop()
{
	if (timerDelay >= 0)
	{
		if ((millis() - timer) >= timerDelay)
		{
			timer = millis();
			timedLoop();
		}
	}
}
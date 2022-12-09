#include "LedEffect.h"
#include <string>

void LedEffect::loop()
{
	if (timerDelay > 0)
	{
		u_long timePassed = (millis() - timer);
		if (timePassed >= timerDelay)
		{
			int repeatLoop = (int)timePassed / timerDelay;
			if (repeatLoop > 4)
				repeatLoop = 4;

			for (int i = 0; i < repeatLoop; i++)
			{
				timedLoop();
			}
			timer = millis();
		}
	}
}
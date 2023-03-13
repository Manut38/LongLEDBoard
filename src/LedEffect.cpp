#include "LedEffect.h"
#include <string>

void LedEffect::loop()
{
	if (timerDelay > 0)
	{
		// calculate delay timer and run timedLoop() when timer is over
		u_long timePassed = (millis() - timer);
		if (timePassed >= timerDelay)
		{
			int repeatLoop = (int)timePassed / timerDelay;
			for (int i = 0; i < repeatLoop; i++)
			{
				timedLoop();
				if (i >= 4)
					break;
			}
			// reset timer
			timer = millis();
		}
	}
	else
	{
		// run timedLoop every cycle
		timedLoop();
	}
}
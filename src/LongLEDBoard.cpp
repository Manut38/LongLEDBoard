#include <Arduino.h>
#include "Config.h"
#include "MPU.h"
#include "LED.h"
#include "WebServer.h"
#include "LedEffect/EffectBlink.h"
#include "LedEffect/EffectColorStrike.h"
#include "LedEffect/EffectRainbowLoop.h"
#include "LedEffect/EffectRainbowStrike.h"

using namespace std;

MPU mpu;
LED led;
WebServer server;
SocketHandler socketHandler(&led);

void setup()
{
	// Initialize Serial
	Serial.begin(BAUD);
	Serial.println("\n🛹 LongLEDBoard Start\n");

	// Initialize components
#ifndef DISABLE_WEBSERVER
	server.setSocketHandler(&socketHandler);
	server.setup();
#endif
#ifndef DISABLE_LED
	led.setup();
#endif
#ifndef DISABLE_MPU
	mpu.setup();
#endif

	// Start default LED effect
	led.effectConfig.bgEffect.solidColor.color = CRGB::Red;
	led.selectBgEffect(BgEffect::SolidColor);

	Serial.println("\n✅ Init complete\n");
}

void handleAcceleration()
{
	if (mpu.wasAccelerated)
	{
		led.fireAccelEffect();
	}
}

void loop()
{

	// Let each component do their work every cycle
#ifndef DISABLE_LED
	led.loop();
#endif
#ifndef DISABLE_MPU
	mpu.loop();
#endif
#ifndef DISABLE_WEBSERVER
	server.loop();
#endif

	handleAcceleration();
}

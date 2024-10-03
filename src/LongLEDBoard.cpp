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

uint32_t effectTestTimer;
uint32_t effectTestTimerDelay = 10000;

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

	// Set LED background effect
	led.effectConfig.bgEffect.solidColor.color = CRGB::BlueViolet;
	led.selectBgEffect(BgEffect::SolidColor);

	// Force first execution of timer
	effectTestTimer = effectTestTimerDelay;

	Serial.println("\n✅ Init complete\n");
}

void handleAccelaration()
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

	handleAccelaration();
}

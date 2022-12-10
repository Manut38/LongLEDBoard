#include <Arduino.h>
#include "Config.h"
#include "MPU.h"
#include "LED.h"
#include "BlinkEffect.h"
#include "ColorRunEffect.h"
#include "WebFrontend.h"

using namespace std;

MPU mpu;
LED led;
WebFrontend frontend;

int buttonState;
int lastButtonState;
u_long effectTestTimer;
int effectTestTimerDelay = 5000;

void setup()
{
	// Initialize Serial
	Serial.begin(115200);

	Serial.println("-------- LongLEDBoard init --------\n");

	// Initialize components
#ifndef DISABLE_WEBFRONTEND
	frontend.setup();
#endif
#ifndef DISABLE_LED
	led.setup();
#endif
#ifndef DISABLE_MPU
	mpu.setup();
#endif

	// Setup pins
	pinMode(BUTTON_PIN, INPUT_PULLUP);

	Serial.println("\n-------- Init complete --------\n");

	// Set LED background effect
	led.setBgEffect(new BlinkEffect(200, 0x003829));

	// Force first execution of timer
	effectTestTimer = effectTestTimerDelay;

	frontend.onFrontendRequest([](FrontendRequestData data)
							   { led.addFgEffect(new ColorRunEffect(data.time, led.getRandomColor(), true)); });
}

void testEffectAfterDelay()
{
	// TEST effects by spawning a new one every 10s
	if (millis() - effectTestTimer >= effectTestTimerDelay)
	{
		effectTestTimer = millis();
		led.addFgEffect(new ColorRunEffect(5000, led.getRandomColor()));
	}
}

void handleButtonPress()
{
	buttonState = digitalRead(BUTTON_PIN);
	if (buttonState == LOW && lastButtonState != LOW)
	{
		// Button pressed
		led.addFgEffect(new ColorRunEffect(5000, led.getRandomColor()));
	}
	lastButtonState = buttonState;
}

void handleAccelaration()
{
	if (mpu.wasAccelerated)
	{
		led.addFgEffect(new ColorRunEffect(2000, led.getRandomColor(), true));
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
#ifndef DISABLE_WEBFRONTEND
	frontend.loop();
#endif

	handleButtonPress();
	handleAccelaration();
	testEffectAfterDelay();
}

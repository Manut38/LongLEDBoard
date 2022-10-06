#include <Arduino.h>
#include "MPU.h"
#include "LED.h"

#define BUTTON_PIN 12

using namespace std;

MPU mpu;
LED led;
int buttonState;
int prevButtonState;

void setup()
{
  // Initialize components
  led.setup();
  mpu.setup();

  // Setup pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

CRGB::HTMLColorCode getRandomColor()
{
  switch (random(4))
  {
  case 0:
    return CRGB::LimeGreen;
  case 1:
    return CRGB::Amethyst;
  case 2:
    return CRGB::Red;
  case 3:
    return CRGB::OrangeRed;
  case 4:
    return CRGB::MediumAquamarine;
  default:
    return CRGB::Red;
  }
}

void loop()
{
  // Let each component do their work every cycle
  led.loop();
  mpu.loop();

  // Handle Button Press
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW && prevButtonState != LOW)
  {
    // Button pressed
    led.startColorRun(getRandomColor(), 20);
    // led.startBlink(getRandomColor(), 200);
  }
  prevButtonState = buttonState;
}
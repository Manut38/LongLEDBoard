#include "LED.h"

void LED::setup()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(255);
}

void LED::loop()
{
    if (millis() - effectStartTime >= effectSpeed)
    {
        effectStartTime = millis();
        switch (currentEffect)
        {
        case COLOR_RUN:
            processColorRun();
            break;
        case BLINK:
            processBlink();
            break;
        case NONE:
            break;
        };
    }
    FastLED.show();
}

void LED::clearEffect()
{
    currentEffect = NONE;
}

void LED::setEffect(LEDEffect effect, CRGB::HTMLColorCode color, int speed)
{
    currentEffect = effect;
    effectStartTime = millis();
    effectColor = color;
    effectSpeed = speed;
}

void LED::startColorRun(CRGB::HTMLColorCode color, int speed)
{
    setEffect(COLOR_RUN, color, speed);
    colorRunCurrentLed = 0;
}

void LED::startBlink(CRGB::HTMLColorCode color, int delay)
{
    setEffect(BLINK, effectColor, delay);
}

void LED::processColorRun()
{
    leds[colorRunCurrentLed++] = effectColor;
    if (colorRunCurrentLed >= NUM_LEDS)
    {
        clearEffect();
    }
    effectStartTime = millis();
}

void LED::processBlink()
{
    if (blinkIsCurrentlyOn)
    {
        fill_solid(leds, NUM_LEDS, CRGB::Black);
    }
    else
    {
        fill_solid(leds, NUM_LEDS, effectColor);
    }
    effectStartTime = millis();
}

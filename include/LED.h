#include <FastLED.h>

#define NUM_LEDS 5
#define LED_PIN 10

class LED
{

private:
    CRGB leds[NUM_LEDS];
    LEDEffect currentEffect;
    int effectSpeed;
    int effectStartTime;
    CRGB::HTMLColorCode effectColor;

    void LED::setEffect(LEDEffect effect, CRGB::HTMLColorCode color, int speed);

    // Effect Color Run
    void processColorRun();
    int colorRunCurrentLed;

    // Effect Blink
    void processBlink();
    bool blinkIsCurrentlyOn;

public:
    void setup();
    void loop();

    void startColorRun(CRGB::HTMLColorCode color, int speed);
    void LED::startBlink(CRGB::HTMLColorCode color, int delay);

    void clearEffect();
};

enum LEDEffect
{
    NONE,
    COLOR_RUN,
    BLINK
};
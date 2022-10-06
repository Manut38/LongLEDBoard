#include <FastLED.h>

#define NUM_LEDS 5
#define LED_PIN 10

enum LEDEffect
{
    NONE,
    COLOR_RUN,
    BLINK
};
class LED
{

private:
    CRGB leds[NUM_LEDS];
    LEDEffect currentEffect;
    int effectSpeed;
    unsigned long effectStartTime;
    CRGB::HTMLColorCode effectColor;

    void setEffect(LEDEffect effect, CRGB::HTMLColorCode color, int speed);

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
    void startBlink(CRGB::HTMLColorCode color, int delay);

    void clearEffect();
};
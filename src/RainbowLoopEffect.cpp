#include "RainbowLoopEffect.h"
#include "FastLED.h"

RainbowLoopEffect::RainbowLoopEffect(int durationFullCycle)
{
    // Calculate hue increment based on the desired duration of one loop
    this->timerDelay = durationFullCycle / timerDelay;
}

void RainbowLoopEffect::timedLoop()
{
    fill_rainbow(mask, NUM_LEDS, hue, 7);
    hue++;
}

#include "LedEffect/EffectRainbowLoop.h"
#include "FastLED.h"

EffectRainbowLoop::EffectRainbowLoop(int durationFullCycle)
{
    // Calculate hue increment based on the desired duration of one loop
    this->timerDelay = durationFullCycle / NUM_LEDS / 2;
}

EffectRainbowLoop::EffectRainbowLoop(LedEffectConfig *effectConfig)
    : EffectRainbowLoop(effectConfig->bgEffect.rainbow.duration)
{
}

void EffectRainbowLoop::timedLoop()
{
    fill_rainbow(mask, NUM_LEDS, hue, 1);
    hue += 1;
}
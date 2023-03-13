#pragma once
#include "LedEffect.h"

class RainbowLoopEffect : public LedEffect
{
private:
    uint8_t hue = 0;
    uint8_t hueIncrement;

protected:
    void timedLoop() override;

public:
    RainbowLoopEffect(int durationFullCycle);
};

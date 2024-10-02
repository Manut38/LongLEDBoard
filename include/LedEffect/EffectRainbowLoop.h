#pragma once
#include "LedEffect.h"

class EffectRainbowLoop : public LedEffect
{
private:
    uint8_t hue = 0;
    uint8_t hueIncrement;

protected:
    void timedLoop() override;

public:
    EffectRainbowLoop(int durationFullCycle);
    EffectRainbowLoop(LedEffectConfig *effectConfig);

    virtual std::unique_ptr<LedEffect> clone() const override
    {
        return std::make_unique<EffectRainbowLoop>(*this);
    }
};

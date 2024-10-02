#pragma once

#include <map>
#include <string>

enum class BgEffect
{
    SolidColor,
    Rainbow,
    Breathing,
    Fire,
    ColorChase,
    ColorFade,
    Sparkle,
};

static std::map<std::string, BgEffect> BgEffectMap{
    {"solid_color", BgEffect::SolidColor},
    {"breathing", BgEffect::Breathing},
    {"rainbow", BgEffect::Rainbow},
    {"fire", BgEffect::Fire},
    {"color_chase", BgEffect::ColorChase},
    {"color_fade", BgEffect::ColorFade},
    {"sparkle", BgEffect::Sparkle},
};

enum class AccelEffect
{
    ColorStrike,
    RainbowStrike,
    GradientStrike,
    ColorChase,
    Strobe,
    RainbowStrobe
};

static std::map<std::string, AccelEffect> AccelEffectMap{
    {"color_strike", AccelEffect::ColorStrike},
    {"rainbow_strike", AccelEffect::RainbowStrike},
    {"gradient_strike", AccelEffect::GradientStrike},
    {"color_chase", AccelEffect::ColorChase},
    {"strobe", AccelEffect::Strobe},
    {"rainbow_strobe", AccelEffect::RainbowStrobe},
};
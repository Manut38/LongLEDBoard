#pragma once

struct SolidColorEffectConfig
{
	CRGB color;
};

struct RainbowEffectConfig
{
	uint16_t duration;
};

struct RainbowStrikeEffectConfig
{
	uint16_t duration;
};

struct ColorStrikeConfig
{
	CRGB color;
	uint16_t duration;
};

struct BgEffectConfig
{
	SolidColorEffectConfig solidColor;
	RainbowEffectConfig rainbow;
};

struct AccelEffectConfig
{
	RainbowStrikeEffectConfig rainbowStrike;
	ColorStrikeConfig colorStrike;
};

struct LedEffectConfig
{
	BgEffectConfig bgEffect;
	AccelEffectConfig accelEffect;
};

import { defineStore } from 'pinia';
import {
  AccelEffect,
  AccelEffectConfig,
  BackgroundEffectConfig,
  BgEffect,
  BoardState,
  PreviewData,
  SteeringEffect,
  SteeringEffectConfig,
} from 'src/types/types';
import { ref } from 'vue';

export const useEffectConfigStore = defineStore(
  'effectConfig',
  () => {
    const boardState = ref<BoardState>({
      active: false,
      bgActive: false,
      bgSelected: BgEffect.SolidColor,
      accelActive: false,
      accelSelected: AccelEffect.ColorStrike,
      steeringActive: false,
      steeringSelected: SteeringEffect.ColorFadeTilt,
      globalBrightness: 255,
    });
    const bgEffectConfig = ref<BackgroundEffectConfig>({
      solidColor: {
        color: '#ffffff',
      },
      rainbow: {
        duration: 5,
      },
      breathing: {
        colors: ['#ffffff'],
        time: 3000,
      },
      colorChase: {
        colors: ['#ffffff'],
        time: 3000,
      },
      colorFade: {
        colors: ['#ffffff'],
        time: 3000,
      },
      fire: {
        speed: 100,
      },
      sparkle: {
        background: '#000000',
        sparkleColor: '#ffffff',
        speed: 100,
      },
    });
    const accelEffectConfig = ref<AccelEffectConfig>({
      colorStrike: {
        color: '#ffffff',
        duration: 500,
      },
      rainbowStrike: { duration: 500 },
      colorChase: { colors: ['#ffffff', '#000000'], time: 500 },
      gradientStrike: { colors: ['#ffffff', '#000000'], duration: 500 },
      rainbowStrobe: { speed: 20 },
      strobe: { color: '#ffffff', speed: 20 },
    });
    const steeringEffectConfig = ref<SteeringEffectConfig>();

    const previewData = ref<PreviewData>();

    return {
      previewData,
      boardState,
      bgEffectConfig,
      accelEffectConfig,
      steeringEffectConfig,
    };
  },
  {
    persist: true,
  }
);

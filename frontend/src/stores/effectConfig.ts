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
      bgSelected: BgEffect.Solid,
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
    const accelEffectConfig = ref<AccelEffectConfig>();
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

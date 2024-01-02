import { defineStore } from 'pinia';
import {
  AccelEffect,
  BackgroundEffectConfig,
  BgEffect,
  BoardEffectState,
  PreviewData,
  SteeringEffect,
} from 'src/types/types';
import { ref } from 'vue';

export const useEffectConfigStore = defineStore(
  'effectConfig',
  () => {
    const boardEffectState = ref<BoardEffectState>({
      active: false,
      bgActive: false,
      bgSelected: BgEffect.Solid,
      accelActive: false,
      accelSelected: AccelEffect.ColorStrike,
      steeringActive: false,
      steeringSelected: SteeringEffect.ColorFadeTilt,
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
    const previewData = ref<PreviewData>();

    return {
      previewData,
      boardEffectState,
      bgEffectConfig,
    };
  },
  {
    persist: true,
  }
);

import { defineStore } from 'pinia';
import {
  AccelEffect,
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
      steeringSelected: SteeringEffect.ColorRightLeft,
    });
    // const effectConfig = ref<EffectConfig>();
    const previewData = ref<PreviewData>();

    return {
      previewData,
      boardEffectState,
      // effectConfig,
    };
  },
  {
    persist: true,
  }
);

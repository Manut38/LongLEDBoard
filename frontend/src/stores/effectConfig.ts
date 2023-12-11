import { defineStore } from 'pinia';
import { BoardEffectState, PreviewData } from 'src/types/types';
import { ref } from 'vue';

export const useEffectConfigStore = defineStore(
  'effectConfig',
  () => {
    const boardEffectState = ref<BoardEffectState>({
      accel_active: false,
      active: false,
      steering_active: false,
      bg_active: false,
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

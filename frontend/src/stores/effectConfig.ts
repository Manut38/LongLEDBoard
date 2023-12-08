import { defineStore } from 'pinia';
import { ref } from 'vue';

export const useEffectConfigStore = defineStore(
  'effectConfig',
  () => {
    const effectsActive = ref<boolean>(false);
    const bgEffectActive = ref<boolean>(false);
    const accelEffectActive = ref<boolean>(false);
    const steeringEffectActive = ref<boolean>(false);

    return {
      effectsActive,
      bgEffectActive,
      accelEffectActive,
      steeringEffectActive,
    };
  },
  {
    persist: true,
  }
);

export interface EffectConfigStore {
  effectsActive: boolean;
  bgEffectActive: boolean;
  accelEffectActive: boolean;
  steeringEffectActive: boolean;
}

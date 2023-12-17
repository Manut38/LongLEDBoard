<template>
  <effect-control-card
    title="Acceleration Effect"
    :effect-list="effectList"
    :active="boardEffectState.accelActive"
    :selected-id="boardEffectState.accelSelected"
    @toggle-active="
      boardEffectState.accelActive = !boardEffectState.accelActive
    "
    @change-selection="(id) => (boardEffectState.accelSelected = id)"
  >
  </effect-control-card>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { AccelEffect } from 'src/types/types';
import { reactive } from 'vue';
import EffectControlCard from './EffectControlCard.vue';

const effectConfigStore = useEffectConfigStore();
const { boardEffectState } = storeToRefs(effectConfigStore);

const effectList = reactive([
  {
    label: 'Color Strike',
    id: AccelEffect.ColorStrike,
  },
  {
    label: 'Rainbow Strike',
    id: AccelEffect.RainbowStrike,
  },
  {
    label: 'Gradient Strike',
    id: AccelEffect.GradientStrike,
  },
  {
    label: 'Color Chase',
    id: AccelEffect.ColorChase,
  },
  {
    label: 'Strobe',
    id: AccelEffect.Strobe,
  },
  {
    label: 'Rainbow Strobe',
    id: AccelEffect.RainbowStrobe,
  },
]);
</script>

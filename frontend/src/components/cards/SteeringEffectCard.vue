<template>
  <effect-control-card
    title="Steering Effect"
    :effect-list="effectList"
    :active="boardEffectState.steeringActive"
    :selected-id="boardEffectState.steeringSelected"
    @toggle-active="
      boardEffectState.steeringActive = !boardEffectState.steeringActive
    "
    @change-selection="(id) => (boardEffectState.steeringSelected = id)"
  >
    <div class="text-center full-width text-grey-5">No Settings</div>
  </effect-control-card>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { SteeringEffect } from 'src/types/types';
import { reactive } from 'vue';
import EffectControlCard from './EffectControlCard.vue';

const effectConfigStore = useEffectConfigStore();
const { boardEffectState } = storeToRefs(effectConfigStore);

const effectList = reactive([
  {
    label: 'Color Fade Tilt',
    id: SteeringEffect.ColorFadeTilt,
  },
  {
    label: 'Water',
    id: SteeringEffect.Water,
  },
]);
</script>

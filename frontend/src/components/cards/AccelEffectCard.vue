<template>
  <effect-control-card
    title="Acceleration Effect"
    :effect-list="effectList"
    :active="boardState.accelActive"
    :selected-id="boardState.accelSelected"
    @toggle-active="
      boardState.accelActive = !boardState.accelActive;
      backend.sendBoardState({ accelActive: boardState.accelActive });
    "
    @change-selection="
      (id) => {
        boardState.accelSelected = id;
        backend.sendBoardState({ accelSelected: id });
      }
    "
  >
    <div class="text-center full-width text-grey-5">No Settings</div>
  </effect-control-card>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { AccelEffect } from 'src/types/types';
import { reactive } from 'vue';
import EffectControlCard from './EffectControlCard.vue';

const effectConfigStore = useEffectConfigStore();
const { boardState: boardState } = storeToRefs(effectConfigStore);

const backend = useBackend();

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

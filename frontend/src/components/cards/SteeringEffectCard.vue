<template>
  <effect-control-card
    title="Steering Effect"
    :effect-list="effectList"
    :active="boardState.steeringActive"
    :selected-id="boardState.steeringSelected"
    @toggle-active="
      boardState.steeringActive = !boardState.steeringActive;
      backend.sendBoardState({ bgActive: boardState.steeringActive });
    "
    @change-selection="
      (id) => {
        boardState.steeringSelected = id;
        backend.sendBoardState({ steeringSelected: id });
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
import { SteeringEffect } from 'src/types/types';
import { reactive } from 'vue';
import EffectControlCard from './EffectControlCard.vue';

const effectConfigStore = useEffectConfigStore();
const { boardState: boardState } = storeToRefs(effectConfigStore);

const backend = useBackend();

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

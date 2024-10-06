<template>
  <effect-control-card
    title="Steering Effect"
    :effect-list="effectList"
    :active="boardState.steeringActive"
    :selected-id="boardState.steeringSelected"
    @toggle-active="
      boardState.steeringActive = !boardState.steeringActive;
      backend.sendBoardState({ steeringActive: boardState.steeringActive });
    "
    @change-selection="changeSelection"
  >
    <q-list>
      <q-item>
        <q-item-section side>
          <q-item-label caption>Sensitivity</q-item-label>
        </q-item-section>
        <q-item-section>
          <q-slider
            v-model="boardState.steeringSensitivity"
            :min="20"
            :max="200"
            @change="
              backend.sendBoardState({
                accelSensitivity: boardState.steeringSensitivity,
              })
            "
          />
        </q-item-section>
      </q-item>
    </q-list>
    <q-separator inset />
    <div class="text-center full-width text-grey-5 q-mt-md">No Settings</div>
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

function changeSelection(selectionId: SteeringEffect) {
  boardState.value.steeringSelected = selectionId;
  backend.sendBoardState({ steeringSelected: selectionId });
}
</script>

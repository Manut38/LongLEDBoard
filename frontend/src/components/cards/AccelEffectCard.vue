<template>
  <effect-control-card
    v-slot="slotProps"
    title="Acceleration Effect"
    :effect-list="effectList"
    :active="boardState.accelActive"
    :selected-id="boardState.accelSelected"
    @toggle-active="
      boardState.accelActive = !boardState.accelActive;
      backend.sendBoardState({ accelActive: boardState.accelActive });
    "
    @change-selection="changeSelection"
  >
    <div
      v-if="slotProps.selected?.id === AccelEffect.ColorStrike"
      class="row justify-center q-gutter-md"
    >
      <q-item-label>Duration</q-item-label>
      <q-slider
        v-model="effectConfigStore.accelEffectConfig.colorStrike.duration"
        :min="500"
        :max="2000"
        label
        @change="
          if ($event != undefined)
            backend.sendEffectConfigState({
              accelEffect: {
                colorStrike: effectConfigStore.accelEffectConfig.colorStrike,
              },
            });
        "
      />
    </div>
    <div
      v-else-if="slotProps.selected?.id === AccelEffect.RainbowStrike"
      class="row justify-center q-gutter-md"
    >
      <q-item-label>Duration</q-item-label>
      <q-slider
        v-model="effectConfigStore.accelEffectConfig.rainbowStrike.duration"
        :min="500"
        :max="2000"
        label
        @change="
          if ($event != undefined)
            backend.sendEffectConfigState({
              accelEffect: {
                rainbowStrike: effectConfigStore.accelEffectConfig.rainbowStrike,
              },
            });
        "
      />
    </div>
    <div v-else class="text-center full-width text-grey-5">No Settings</div>
  </effect-control-card>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { AccelEffect, AccelEffectConfigState } from 'src/types/types';
import { reactive } from 'vue';
import EffectControlCard from './EffectControlCard.vue';

const effectConfigStore = useEffectConfigStore();
const { boardState, accelEffectConfig } = storeToRefs(effectConfigStore);

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

function changeSelection(selectionId: AccelEffect) {
  boardState.value.accelSelected = selectionId;
  let effectState: AccelEffectConfigState = {};
  switch (selectionId) {
    case AccelEffect.ColorStrike:
      effectState.colorStrike = accelEffectConfig.value.colorStrike;
      break;
    case AccelEffect.RainbowStrike:
      effectState.rainbowStrike = accelEffectConfig.value.rainbowStrike;
      break;
  }
  backend.sendEffectConfigState({
    accelEffect: effectState,
  });
  backend.sendBoardState({ accelSelected: selectionId });
}
</script>

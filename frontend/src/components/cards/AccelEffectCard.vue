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
    <div class="row justify-center q-gutter-md">
      <color-strike-effect-control v-if="slotProps.selected?.id === AccelEffect.ColorStrike"/>
      <rainbow-strike-effect-config v-else-if="slotProps.selected?.id === AccelEffect.RainbowStrike" />
      <div v-else class="text-center full-width text-grey-5">No Settings</div>
    </div>
  </effect-control-card>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { AccelEffect } from 'src/types/types';
import { reactive } from 'vue';
import ColorStrikeEffectControl from '../effect-controls/ColorStrikeEffectControl.vue';
import RainbowStrikeEffectConfig from '../effect-controls/RainbowStrikeEffectConfig.vue';
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
  backend.sendBoardState({ accelSelected: selectionId });
}
</script>

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
    <q-list>
      <q-item>
        <q-item-section side>
          <q-item-label caption>Sensitivity</q-item-label>
        </q-item-section>
        <q-item-section>
          <q-slider
            v-model="boardState.accelSensitivity"
            :min="20"
            :max="200"
            @change="
              backend.sendBoardState({
                accelSensitivity: boardState.accelSensitivity,
              })
            "
          />
        </q-item-section>
      </q-item>
    </q-list>
    <q-separator inset />

    <color-strike-effect-control
      v-if="slotProps.selected?.id === AccelEffect.ColorStrike"
    />
    <rainbow-strike-effect-config
      v-else-if="slotProps.selected?.id === AccelEffect.RainbowStrike"
    />
    <div v-else class="text-center full-width text-grey-5 q-mt-md">
      No Settings
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
const { boardState } = storeToRefs(effectConfigStore);

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

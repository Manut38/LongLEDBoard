<template>
  <q-item-label>Duration</q-item-label>
      <q-slider
        v-model="effectConfigStore.accelEffectConfig.colorStrike.duration"
        :min="500"
        :max="2000"
        label
        @change="sendEffectConfigState"
      />
      <v-color-picker
        v-model="effectConfigStore.accelEffectConfig.colorStrike.color"
        flat
        hide-inputs
        mode="rgb"
        show-swatches
        swatches-max-height="120"
        @update:model-value="sendEffectConfigState"
      ></v-color-picker>
</template>

<script setup lang="ts">
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';

const effectConfigStore = useEffectConfigStore();

const backend = useBackend();

function sendEffectConfigState() {
  backend.sendEffectConfigState({
    accelEffect: {
      colorStrike: effectConfigStore.accelEffectConfig.colorStrike,
    },
  });
}
</script>




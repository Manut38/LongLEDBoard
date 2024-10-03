<template>
  <q-item-label>Duration</q-item-label>
  <q-slider
    v-model="effectConfigStore.accelEffectConfig.rainbowStrike.duration"
    :min="500"
    :max="10000"
    label
    @change="sendEffectConfigState"
  />
</template>

<script setup lang="ts">
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';

const effectConfigStore = useEffectConfigStore();

const backend = useBackend();

function sendEffectConfigState() {
  backend.sendEffectConfigState({
    accelEffect: {
      rainbowStrike: effectConfigStore.accelEffectConfig.rainbowStrike,
    },
  });
}
</script>

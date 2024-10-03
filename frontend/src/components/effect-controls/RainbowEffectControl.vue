<template>
  <q-item-label>Duration</q-item-label>
  <q-slider
    v-model="effectConfigStore.bgEffectConfig.rainbow.duration"
    :min="1000"
    :max="5000"
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
    bgEffect: {
      rainbow: effectConfigStore.bgEffectConfig.rainbow,
    },
  });
}
</script>

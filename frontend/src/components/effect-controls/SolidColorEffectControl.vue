<template>
  <v-color-picker
          v-model="effectConfigStore.bgEffectConfig.solidColor.color"
          flat
          hide-inputs
          mode="rgb"
          show-swatches
          swatches-max-height="120"
          @update:model-value="sendEffectConfigState"
        ></v-color-picker>
        <!-- <q-color v-model="effectConfigStore.bgEffectConfig.solidColor.color" no-header/> -->
</template>

<script setup lang="ts">
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';

const effectConfigStore = useEffectConfigStore();

const backend = useBackend();

function sendEffectConfigState() {
  backend.sendEffectConfigState({
    bgEffect: {
      solidColor: effectConfigStore.bgEffectConfig.solidColor,
    },
  });
}
</script>




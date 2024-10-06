<template>
  <q-list>
    <EffectColorPicker
      :color="bgEffectConfig.solidColor.color"
      @color-changed="
        {
          bgEffectConfig.solidColor.color = $event;
          sendEffectConfigState();
        }
      "
    />
  </q-list>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import EffectColorPicker from './components/EffectColorPicker.vue';

const { bgEffectConfig } = storeToRefs(useEffectConfigStore());

const backend = useBackend();

function sendEffectConfigState() {
  backend.sendEffectConfigState({
    bgEffect: {
      solidColor: bgEffectConfig.value.solidColor,
    },
  });
}
</script>

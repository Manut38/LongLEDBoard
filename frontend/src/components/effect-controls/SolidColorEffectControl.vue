<template>
  <q-list>
    <ColorPickerItem
      label="Color"
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
import ColorPickerItem from './components/ColorPickerItem.vue';

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

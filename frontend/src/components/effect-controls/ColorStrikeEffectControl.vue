<template>
  <q-list>
    <q-item>
      <q-item-section side>
        <q-item-label caption>Duration</q-item-label>
      </q-item-section>
      <q-item-section>
        <q-slider
          v-model="accelEffectConfig.colorStrike.duration"
          :min="500"
          :max="2000"
          @change="sendEffectConfigState"
        />
      </q-item-section>
    </q-item>
    <ColorPickerItem
      label="Color"
      :color="accelEffectConfig.colorStrike.color"
      @color-changed="
        {
          accelEffectConfig.colorStrike.color = $event;
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

const { accelEffectConfig } = storeToRefs(useEffectConfigStore());

const backend = useBackend();

function sendEffectConfigState() {
  backend.sendEffectConfigState({
    accelEffect: {
      colorStrike: accelEffectConfig.value.colorStrike,
    },
  });
}
</script>

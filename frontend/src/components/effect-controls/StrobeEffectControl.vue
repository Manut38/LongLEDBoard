<template>
  <q-list>
    <q-item>
      <q-item-section side>
        <q-item-label caption>Speed</q-item-label>
      </q-item-section>
      <q-item-section>
        <q-slider
          v-model="accelEffectConfig.strobe.speed"
          :min="1"
          :max="150"
          @change="sendEffectConfigState"
        />
      </q-item-section>
    </q-item>
    <EffectColorPicker
      label="Strobe Color"
      :color="accelEffectConfig.strobe.color"
      @color-changed="
        {
          accelEffectConfig.strobe.color = $event;
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

const { accelEffectConfig } = storeToRefs(useEffectConfigStore());

const backend = useBackend();

function sendEffectConfigState() {
  backend.sendEffectConfigState({
    accelEffect: {
      strobe: accelEffectConfig.value.strobe,
    },
  });
}
</script>

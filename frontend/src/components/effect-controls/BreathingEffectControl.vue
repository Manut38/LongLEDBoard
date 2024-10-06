<template>
  <q-list>
    <q-item>
      <q-item-section side>
        <q-item-label caption>Duration</q-item-label>
      </q-item-section>
      <q-item-section>
        <q-slider
          v-model="bgEffectConfig.breathing.time"
          :min="500"
          :max="10000"
          @change="sendEffectConfigState"
        />
      </q-item-section>
    </q-item>
    <EffectColorPicker
      label="Color"
      :color="bgEffectConfig.breathing.colors[0]"
      @color-changed="
        {
          // bgEffectConfig.breathing.colors = $event;
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
      breathing: bgEffectConfig.value.breathing,
    },
  });
}
</script>

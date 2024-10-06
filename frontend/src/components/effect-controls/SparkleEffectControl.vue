<template>
  <q-list>
    <q-item>
      <q-item-section side>
        <q-item-label caption>Speed</q-item-label>
      </q-item-section>
      <q-item-section>
        <q-slider
          v-model="bgEffectConfig.sparkle.speed"
          :min="3"
          :max="50"
          @change="sendEffectConfigState"
        />
      </q-item-section>
    </q-item>
    <EffectColorPicker
      label="Background"
      :color="bgEffectConfig.sparkle.background"
      @color-changed="
        {
          bgEffectConfig.sparkle.background = $event;
          sendEffectConfigState();
        }
      "
    />
    <EffectColorPicker
      label="Sparkles"
      :color="bgEffectConfig.sparkle.sparkleColor"
      @color-changed="
        {
          bgEffectConfig.sparkle.sparkleColor = $event;
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
      sparkle: bgEffectConfig.value.sparkle,
    },
  });
}
</script>

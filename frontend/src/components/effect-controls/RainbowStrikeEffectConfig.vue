<template>
  <q-list>
    <q-item>
      <q-item-section side>
        <q-item-label caption>Duration</q-item-label>
      </q-item-section>
      <q-item-section>
        <q-slider
          v-model="accelEffectConfig.rainbowStrike.duration"
          :min="500"
          :max="10000"
          @change="sendEffectConfigState"
        />
      </q-item-section>
    </q-item>
  </q-list>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';

const { accelEffectConfig } = storeToRefs(useEffectConfigStore());

const backend = useBackend();

function sendEffectConfigState() {
  backend.sendEffectConfigState({
    accelEffect: {
      rainbowStrike: accelEffectConfig.value.rainbowStrike,
    },
  });
}
</script>

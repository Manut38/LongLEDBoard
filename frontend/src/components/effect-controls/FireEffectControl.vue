<template>
  <q-list>
    <q-item>
      <q-item-section side>
        <q-item-label caption>Speed</q-item-label>
      </q-item-section>
      <q-item-section>
        <q-slider
          v-model="bgEffectConfig.fire.speed"
          :min="2"
          :max="50"
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

const { bgEffectConfig } = storeToRefs(useEffectConfigStore());

const backend = useBackend();

function sendEffectConfigState() {
  backend.sendEffectConfigState({
    bgEffect: {
      fire: bgEffectConfig.value.fire,
    },
  });
}
</script>

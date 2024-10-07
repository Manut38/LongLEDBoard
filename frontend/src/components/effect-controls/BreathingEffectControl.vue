<template>
  <q-list class="full-width">
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
    <ColorListItem
      v-model="bgEffectConfig.breathing.colors"
      label="Color List"
      @update:model-value="sendEffectConfigState"
      @touchstart.stop
    ></ColorListItem>
  </q-list>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import ColorListItem from './components/ColorListItem.vue';

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

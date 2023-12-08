<template>
  <effect-control-card
    title="Acceleration Effect"
    :list-of-effects="listOfEffects"
    :active="accelEffectActive"
    @toggle-active="accelEffectActive = !accelEffectActive"
  >
  </effect-control-card>
</template>

<script setup lang="ts">
import { reactive, ref } from 'vue';
import EffectControlCard from './EffectControlCard.vue';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { storeToRefs } from 'pinia';

// const props = defineProps<{

// }>()

const effectConfigStore = useEffectConfigStore();
const { accelEffectActive } = storeToRefs(effectConfigStore);
const listOfEffects = reactive([
  'Rumble',
  'Lightning',
  'Rainbow Strike',
  'Fire Strike',
]);
</script>

<template>
  <effect-control-card
    title="Acceleration Effect"
    :list-of-effects="listOfEffects"
    :active="boardEffectState.accelActive"
    @toggle-active="boardEffectState.accelActive = !boardEffectState.accelActive"
  >
  </effect-control-card>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { reactive } from 'vue';
import EffectControlCard from './EffectControlCard.vue';

// const props = defineProps<{

// }>()

const effectConfigStore = useEffectConfigStore();
const { boardEffectState } = storeToRefs(effectConfigStore);
const listOfEffects = reactive([
  'Rumble',
  'Lightning',
  'Rainbow Strike',
  'Fire Strike',
]);
</script>

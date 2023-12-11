<template>
  <effect-control-card
    title="Steering Effect"
    :list-of-effects="listOfEffects"
    :active="boardEffectState.steeringActive"
    @toggle-active="boardEffectState.steeringActive = !boardEffectState.steeringActive"
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
const listOfEffects = reactive(['Color Fade Left/Right']);
</script>

<template>
  <effect-control-card
    title="Steering Effect"
    :list-of-effects="listOfEffects"
    :active="steeringEffectActive"
    @toggle-active="steeringEffectActive = !steeringEffectActive"
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
const { steeringEffectActive } = storeToRefs(effectConfigStore);
const listOfEffects = reactive(['Color Fade Left/Right']);
</script>

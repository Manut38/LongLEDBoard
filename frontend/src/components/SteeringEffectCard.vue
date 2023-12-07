<template>
  <effect-control-card title="Steering Effect" :list-of-effects="listOfEffects">
  </effect-control-card>
</template>

<script setup lang="ts">
import { reactive, ref } from 'vue';
import EffectControlCard from './EffectControlCard.vue';

// const props = defineProps<{

// }>()

const listOfEffects = reactive(['Color Fade Left/Right']);

</script>

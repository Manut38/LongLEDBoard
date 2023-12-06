<template>
  <effect-control-card title="Acceleration" :list-of-effects="listOfEffects">
  </effect-control-card>
</template>

<script setup lang="ts">
import { reactive, ref } from 'vue';
import EffectControlCard from './EffectControlCard.vue';

// const props = defineProps<{

// }>()

const listOfEffects = reactive([
  'Rumble',
  'Lightning',
  'Rainbow Strike',
  'Fire Strike',
]);

</script>

<template>
  <effect-control-card
    title="Background Effect"
    :list-of-effects="listOfEffects"
    v-slot="slotProps"
  >
    <div
      v-if="slotProps.effectSelection == 'Solid Color'"
      class="row items-center justify-center q-gutter-md"
    >
      <q-color v-model="bgSolidColor" no-header />
    </div>
  </effect-control-card>
</template>

<script setup lang="ts">
import { reactive, ref } from 'vue';
import EffectControlCard from './EffectControlCard.vue';

// const props = defineProps<{

// }>()

const listOfEffects = reactive(['Rainbow', 'Fire', 'Solid Color']);

const bgSolidColor = ref<string>();
</script>

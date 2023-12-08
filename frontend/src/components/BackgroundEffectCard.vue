<template>
  <effect-control-card
    title="Background Effect"
    :list-of-effects="listOfEffects"
    :active="bgEffectActive"
    @toggle-active="bgEffectActive = !bgEffectActive"
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
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { storeToRefs } from 'pinia';

// const props = defineProps<{

// }>()
const effectConfigStore = useEffectConfigStore();
const { bgEffectActive } = storeToRefs(effectConfigStore);

const listOfEffects = reactive(['Rainbow', 'Fire', 'Solid Color']);

const bgSolidColor = ref<string>();
</script>

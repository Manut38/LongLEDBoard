<template>
  <effect-control-card
    v-slot="slotProps"
    title="Background Effect"
    :list-of-effects="listOfEffects"
    :active="boardEffectState.bgActive"
    @toggle-active="boardEffectState.bgActive = !boardEffectState.bgActive"
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
import { storeToRefs } from 'pinia';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { reactive, ref } from 'vue';
import EffectControlCard from './EffectControlCard.vue';

// const props = defineProps<{

// }>()
const effectConfigStore = useEffectConfigStore();
const { boardEffectState } = storeToRefs(effectConfigStore);

const listOfEffects = reactive(['Rainbow', 'Fire', 'Solid Color']);

const bgSolidColor = ref<string>();
</script>

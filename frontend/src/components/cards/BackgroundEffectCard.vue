<template>
  <effect-control-card
    v-slot="slotProps"
    title="Background Effect"
    :effect-list="effectList"
    :active="boardEffectState.bgActive"
    :selected-id="boardEffectState.bgSelected"
    @toggle-active="boardEffectState.bgActive = !boardEffectState.bgActive"
    @change-selection="(id) => (boardEffectState.bgSelected = id)"
  >
    <div
      v-if="slotProps.selected?.id === BgEffect.Solid"
      class="row justify-center q-gutter-md"
    >
      <v-color-picker
        v-model="effectConfigStore.bgEffectConfig.solidColor.color"
        flat
        hide-inputs
        mode="rgb"
        show-swatches
        swatches-max-height="120"
      ></v-color-picker>
      <q-separator vertical></q-separator>
      <div class="q-gutter-sm col-2">
        <div class="text-body1">Presets</div>
        <q-btn
          outline
          no-wrap
          label="Save"
          icon="eva-save-outline"
          color="primary"
        ></q-btn>
        <q-btn
          outline
          no-wrap
          label="Delete"
          icon="eva-trash-2-outline"
          color="red-8"
        ></q-btn>
      </div>
    </div>
    <div v-else class="text-center full-width text-grey-5">No Settings</div>
  </effect-control-card>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { BgEffect, EffectListEntry } from 'src/types/types';
import { reactive } from 'vue';
import { VColorPicker } from 'vuetify/components/VColorPicker';
import EffectControlCard from './EffectControlCard.vue';

const effectConfigStore = useEffectConfigStore();
const { boardEffectState } = storeToRefs(effectConfigStore);

const effectList: EffectListEntry[] = reactive([
  {
    label: 'Solid',
    id: BgEffect.Solid,
  },
  {
    label: 'Breathing',
    id: BgEffect.Breathing,
  },
  {
    label: 'Fire',
    id: BgEffect.Fire,
  },
  {
    label: 'Color Chase',
    id: BgEffect.ColorChase,
  },
  {
    label: 'Color Fade',
    id: BgEffect.ColorFade,
  },
  {
    label: 'Sparkle',
    id: BgEffect.Sparkle,
  },
]);
</script>

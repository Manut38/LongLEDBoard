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
      <q-color v-model="bgSolidColor" class="darker" no-header />
      <q-separator vertical></q-separator>
      <div class="q-gutter-y-sm col-2">
        <div class="text-body1">Presets</div>
        <q-scroll-area style="height: 200px; width: 6rem">
          <div class="q-gutter-y-sm">
            <div
              v-for="preset in solidColorPresets"
              :key="preset"
              class="row no-wrap q-gutter-x-sm"
            >
              <q-btn
                flat
                class="preset-button"
                :style="'background-color:' + preset + ';'"
                @click="bgSolidColor = preset"
              ></q-btn>
              <q-btn
                dense
                outline
                size="xs"
                icon="close"
                color="grey-5"
              ></q-btn>
            </div>
          </div>
        </q-scroll-area>
      </div>
    </div>
    <div v-else class="text-center full-width text-grey-5">No Settings</div>
  </effect-control-card>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { BgEffect, EffectListEntry } from 'src/types/types';
import { reactive, ref } from 'vue';
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

const bgSolidColor = ref<string>();

// DEMO
const solidColorPresets = reactive([
  '#f66244',
  '#00fffc',
  '#ed00c8',
  '#f66244',
  '#00fffc',
  '#ed00c8',
  '#f66244',
  '#00fffc',
  '#ed00c8',
  '#f66244',
  '#00fffc',
  '#ed00c8',
  '#f66244',
  '#00fffc',
  '#ed00c8',
]);
</script>

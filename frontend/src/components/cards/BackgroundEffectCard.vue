<template>
  <effect-control-card
    v-slot="slotProps"
    title="Background Effect"
    :effect-list="effectList"
    :active="boardState.bgActive"
    :selected-id="boardState.bgSelected"
    @toggle-active="
      boardState.bgActive = !boardState.bgActive;
      backend.sendBoardState({ bgActive: boardState.bgActive });
    "
    @change-selection="changeSelection"
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
        @update:model-value="
          backend.sendEffectConfigState({
            bgEffect: { solidColor: { color: $event } },
          })
        "
      ></v-color-picker>
      <!-- <q-color v-model="effectConfigStore.bgEffectConfig.solidColor.color" no-header class="my-picker" /> -->
      <!-- <q-separator vertical></q-separator> -->
      <!-- <div class="q-gutter-sm col-2">
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
      </div> -->
    </div>
    <div
      v-else-if="slotProps.selected?.id === BgEffect.Rainbow"
      class="row justify-center q-gutter-md"
    >
      <q-item-label>Duration</q-item-label>
      <q-slider
        v-model="effectConfigStore.bgEffectConfig.rainbow.duration"
        :min="1000"
        :max="10000"
        label
        @update:model-value="
          if ($event != undefined)
            backend.sendEffectConfigState({
              bgEffect: { rainbow: { duration: $event } },
            });
        "
        @mousedown.stop
        @touchstart.stop
        @click.stop
      />
    </div>
    <div v-else class="text-center full-width text-grey-5">No Settings</div>
  </effect-control-card>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import {
  BackgroundEffectConfigState,
  BgEffect,
  EffectListEntry,
} from 'src/types/types';
import { reactive } from 'vue';
import { VColorPicker } from 'vuetify/components/VColorPicker';
import EffectControlCard from './EffectControlCard.vue';

const effectConfigStore = useEffectConfigStore();
const { boardState, bgEffectConfig } = storeToRefs(effectConfigStore);

const backend = useBackend();

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
    label: 'Rainbow',
    id: BgEffect.Rainbow,
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

function changeSelection(selectionId: BgEffect) {
  boardState.value.bgSelected = selectionId;
  let effectState: BackgroundEffectConfigState = {};
  switch (selectionId) {
    case BgEffect.Solid:
      effectState.solidColor = bgEffectConfig.value.solidColor;
      break;
    case BgEffect.Rainbow:
      effectState.rainbow = bgEffectConfig.value.rainbow;
      break;
  }
  backend.sendEffectConfigState({
    bgEffect: effectState,
  });
  backend.sendBoardState({ bgSelected: selectionId });
}
</script>

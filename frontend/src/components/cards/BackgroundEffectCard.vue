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
    <solid-color-effect-control
      v-if="slotProps.selected?.id === BgEffect.SolidColor"
    />
    <rainbow-effect-control
      v-else-if="slotProps.selected?.id === BgEffect.Rainbow"
    />
    <breathing-effect-control
      v-else-if="slotProps.selected?.id === BgEffect.Breathing"
    />
    <fire-effect-control v-else-if="slotProps.selected?.id === BgEffect.Fire" />
    <sparkle-effect-control
      v-else-if="slotProps.selected?.id === BgEffect.Sparkle"
    />

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

    <div v-else class="text-center full-width text-grey-5">No Settings</div>
  </effect-control-card>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { BgEffect, EffectListEntry } from 'src/types/types';
import { reactive } from 'vue';
import BreathingEffectControl from '../effect-controls/BreathingEffectControl.vue';
import FireEffectControl from '../effect-controls/FireEffectControl.vue';
import RainbowEffectControl from '../effect-controls/RainbowEffectControl.vue';
import SolidColorEffectControl from '../effect-controls/SolidColorEffectControl.vue';
import SparkleEffectControl from '../effect-controls/SparkleEffectControl.vue';
import EffectControlCard from './EffectControlCard.vue';

const effectConfigStore = useEffectConfigStore();
const { boardState } = storeToRefs(effectConfigStore);

const backend = useBackend();

const effectList: EffectListEntry[] = reactive([
  {
    label: 'Solid',
    id: BgEffect.SolidColor,
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
  backend.sendBoardState({ bgSelected: selectionId });
}
</script>

<template>
  <q-page class="constrain q-pa-md page-padding-preview">
    <q-card
      class="main-elements effect-control-card"
      :class="{ selected: effectsActiveSelected }"
      flat
      bordered
    >
      <q-card-section
        class="row justify-between cursor-pointer"
        style="margin-right: 16px"
        @click="effectsActive = !effectsActive"
        @mousedown="effectsActiveSelected = true"
        @mouseup="effectsActiveSelected = false"
        @touchstart="effectsActiveSelected = true"
        @touchend="effectsActiveSelected = false"
      >
        <div class="text-h6">Effects</div>
        <q-icon
          name="power_settings_new"
          size="2em"
          :color="effectsActive ? 'green-8' : 'red-8'"
        >
        </q-icon>
      </q-card-section>
      <q-separator inset />
      <q-card-section horizontal>
        <div class="q-pa-md column items-stretch full-width q-gutter-y-md">
          <background-effect-card-vue class=""></background-effect-card-vue>
          <accel-effect-card class=""></accel-effect-card>

          <steering-effect-card class=""></steering-effect-card>
        </div>
      </q-card-section>
    </q-card>
    <q-page-sticky expand position="bottom" class="q-ma-md">
      <q-card flat class="full-width constrain">
        <q-expansion-item
          v-model="isPreviewVisible"
          label="Preview"
          class="text-h6"
          expand-icon-class="preview-expand-icon"
        >
          <q-card-section>
            <div class="row no-wrap items-start justify-left q-gutter-x-md">
              <q-skeleton v-if="false" class="text-h6 col-grow" type="rect" />
              <div class="preview-gradient self-center col-grow text-h6"></div>
            </div>
          </q-card-section>
        </q-expansion-item>
      </q-card>
    </q-page-sticky>
  </q-page>
</template>

<script setup lang="ts">
import { storeToRefs } from 'pinia';
import AccelEffectCard from 'src/components/AccelEffectCard.vue';
import BackgroundEffectCardVue from 'src/components/BackgroundEffectCard.vue';
import SteeringEffectCard from 'src/components/SteeringEffectCard.vue';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { ref } from 'vue';

const effectConfigStore = useEffectConfigStore();
const { effectsActive } = storeToRefs(effectConfigStore);

const isPreviewVisible = ref<boolean>();
const effectsActiveSelected = ref<boolean>();
</script>

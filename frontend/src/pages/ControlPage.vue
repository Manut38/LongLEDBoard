<template>
  <q-page class="constrain q-pa-md page-padding-preview">
    <q-card
      class="main-elements effect-control-card"
      :class="{ selected: effectsActiveSelected }"
      bordered
    >
      <q-card-section
        class="row justify-between cursor-pointer"
        @click="boardEffectState.active = !boardEffectState.active"
        @mousedown="effectsActiveSelected = true"
        @mouseup="effectsActiveSelected = false"
        @touchstart="effectsActiveSelected = true"
        @touchend="effectsActiveSelected = false"
      >
        <div class="text-h6 flex items-center">Effects</div>
        <q-space></q-space>
        <q-item class="col-7">
          <q-item-section avatar>
            <q-icon color="white" name="eva-sun-outline" />
          </q-item-section>
          <q-item-section>
            <q-slider
              :model-value="boardEffectState.globalBrightness"
              :min="0"
              :max="255"
              label
              @change="
                (val) => {
                  boardEffectState.globalBrightness = val;
                }
              "
            />
          </q-item-section>
        </q-item>
        <q-toggle v-model="boardEffectState.active" color="primary"></q-toggle>
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
    <q-card
      class="main-elements effect-control-card"
      :class="{ selected: debugActiveSelected }"
      bordered
    >
      <q-card-section
        class="row justify-between cursor-pointer"
        @click="debugActive = !debugActive"
        @mousedown="debugActiveSelected = true"
        @mouseup="debugActiveSelected = false"
        @touchstart="debugActiveSelected = true"
        @touchend="debugActiveSelected = false"
      >
        <div class="text-h6">Debug</div>
        <q-space></q-space>
        <q-toggle v-model="debugActive" color="primary"></q-toggle>
      </q-card-section>
      <q-slide-transition>
        <div v-if="debugActive">
          <q-separator inset></q-separator>
          <q-card-section class="column q-gutter-md no-wrap">
            <q-btn
              label="Test"
              rounded
              outline
              color="primary"
              @click="backend.send('test')"
            ></q-btn>
            <q-list bordered separator class="col-grow">
              <q-item v-ripple clickable>
                <q-item-section>
                  <q-item-label overline>WebSocket Status</q-item-label>
                  <q-item-label>{{ backend.status.value }}</q-item-label>
                </q-item-section>
              </q-item>
              <q-item v-ripple clickable>
                <q-item-section>
                  <q-item-label overline>Socket Response</q-item-label>
                  <q-item-label style="word-wrap: break-word">{{
                    backend.data.value
                  }}</q-item-label>
                </q-item-section>
              </q-item>
              <q-item v-ripple clickable>
                <q-item-section>
                  <q-item-label overline>Store Board Effect State</q-item-label>
                  <q-item-label>{{ boardEffectState }}</q-item-label>
                </q-item-section>
              </q-item>
            </q-list>
          </q-card-section>
        </div>
      </q-slide-transition>
    </q-card>

    <q-page-sticky expand position="bottom" class="q-ma-md">
      <q-card class="darker full-width">
        <q-expansion-item
          v-model="isPreviewVisible"
          popup
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
import AccelEffectCard from 'src/components/cards/AccelEffectCard.vue';
import BackgroundEffectCardVue from 'src/components/cards/BackgroundEffectCard.vue';
import SteeringEffectCard from 'src/components/cards/SteeringEffectCard.vue';
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { ref } from 'vue';

import { useAppConfigStore } from 'src/stores/appConfig';

const effectConfigStore = useEffectConfigStore();
const { boardEffectState } = storeToRefs(effectConfigStore);
const { debugActive } = storeToRefs(useAppConfigStore());

const backend = useBackend();

const isPreviewVisible = ref<boolean>();
const effectsActiveSelected = ref<boolean>();

const debugActiveSelected = ref<boolean>();
</script>

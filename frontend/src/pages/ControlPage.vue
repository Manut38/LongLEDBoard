<template>
  <q-page class="constrain q-pa-md page-padding-preview">
    <q-card
      class="main-elements pressable-card"
      :class="{ selected: effectsActiveSelected }"
      bordered
    >
      <q-card-section
        class="row justify-between cursor-pointer"
        @click="
          boardState.active = !boardState.active;
          backend.sendBoardState({ active: boardState.active });
        "
        @mousedown="effectsActiveSelected = true"
        @mouseup="effectsActiveSelected = false"
        @touchstart="effectsActiveSelected = true"
        @touchend="effectsActiveSelected = false"
      >
        <div class="text-h6 flex items-center">Effects</div>
        <q-space></q-space>
        <q-item class="col-7">
          <q-item-section side>
            <q-icon color="white" name="eva-sun-outline" />
          </q-item-section>
          <q-item-section>
            <q-slider
              v-model="boardState.globalBrightness"
              :min="0"
              :max="255"
              label
              @update:model-value="
                if ($event != undefined)
                  backend.sendBoardState({ globalBrightness: $event });
              "
              @mousedown.stop
              @touchstart.stop
              @click.stop
            />
          </q-item-section>
        </q-item>
        <q-toggle
          v-model="boardState.active"
          color="primary"
          @update:model-value="backend.sendBoardState({ active: $event })"
        ></q-toggle>
      </q-card-section>
      <q-separator inset />
      <q-card-section v-if="q.screen.gt.sm">
        <div
          class="column row-md items-md-start justify-center full-width q-gutter-y-md q-gutter-md-x-md"
        >
          <background-effect-card></background-effect-card>
          <accel-effect-card></accel-effect-card>
          <steering-effect-card></steering-effect-card>
        </div>
      </q-card-section>
      <q-card-section v-if="q.screen.lt.md" class="q-pb-none">
        <q-tabs
          v-model="activeTab"
          align="center"
          narrow-indicator
          dense
          no-caps
          indicator-color="primary"
        >
          <q-tab name="bg" icon="eva-loader-outline" label="Idle" />
          <q-tab name="accel" icon="mdi-speedometer" label="Kick" />
          <q-tab name="steering" icon="mdi-steering" label="Steering" />
        </q-tabs>
      </q-card-section>
      <q-tab-panels
        v-if="q.screen.lt.md"
        v-model="activeTab"
        animated
        swipeable
        infinite
        transition-prev="jump-right"
        transition-next="jump-left"
      >
        <q-tab-panel name="bg">
          <BackgroundEffectCard></BackgroundEffectCard>
        </q-tab-panel>

        <q-tab-panel name="accel">
          <AccelEffectCard></AccelEffectCard>
        </q-tab-panel>

        <q-tab-panel name="steering">
          <SteeringEffectCard></SteeringEffectCard>
        </q-tab-panel>
      </q-tab-panels>
    </q-card>
    <q-card
      class="main-elements pressable-card"
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
          <q-separator inset />
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
                  <q-item-label>{{ boardState }}</q-item-label>
                </q-item-section>
              </q-item>
            </q-list>
          </q-card-section>
        </div>
      </q-slide-transition>
    </q-card>

    <q-page-sticky v-if="false" expand position="bottom" class="q-ma-md">
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
import BackgroundEffectCard from 'src/components/cards/BackgroundEffectCard.vue';
import SteeringEffectCard from 'src/components/cards/SteeringEffectCard.vue';
import { useBackend } from 'src/composables/backend';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { ref } from 'vue';

import { useQuasar } from 'quasar';
import { useAppConfigStore } from 'src/stores/appConfig';

const effectConfigStore = useEffectConfigStore();
const { boardState } = storeToRefs(effectConfigStore);
const { debugActive } = storeToRefs(useAppConfigStore());

const backend = useBackend();
const q = useQuasar();

const isPreviewVisible = ref<boolean>();
const effectsActiveSelected = ref<boolean>();
const activeTab = ref<string>('bg');
const debugActiveSelected = ref<boolean>();
</script>

<template>
  <q-page class="constrain q-pa-md">
    <q-card
      class="main-elements"
      flat
      bordered
      :style="
        isPreviewVisible
          ? ''
          : 'background-color: transparent; border-color: transparent'
      "
    >
      <q-expansion-item
        label="Preview"
        v-model="isPreviewVisible"
        dense
        class="text-h6"
        switch-toggle-side
      >
        <q-card-section>
          <div class="row no-wrap items-start justify-left q-gutter-x-md">
            <q-skeleton v-if="false" class="text-h6 col-grow" type="rect" />
            <div class="preview-gradient self-center col-grow text-h6"></div>
          </div>
        </q-card-section>
      </q-expansion-item>
    </q-card>

    <q-card class="main-elements" flat bordered>
      <q-card-section>
        <div class="text-h6">Effects</div>
      </q-card-section>
      <q-separator inset />
      <q-card-section horizontal>
        <div class="q-pa-md column items-stretch full-width q-gutter-y-md">
          <background-effect-card-vue
            class=""
          ></background-effect-card-vue>
          <accel-effect-card class=""></accel-effect-card>

          <steering-effect-card class=""></steering-effect-card>
        </div>
      </q-card-section>
    </q-card>
  </q-page>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import SteeringEffectCard from 'src/components/SteeringEffectCard.vue';
import BackgroundEffectCardVue from 'src/components/BackgroundEffectCard.vue';
import AccelEffectCard from 'src/components/AccelEffectCard.vue';

const isPreviewVisible = ref<boolean>();
</script>

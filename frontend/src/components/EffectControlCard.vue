<template>
  <q-card
    class="effect-control-card"
    :class="{ active: effectActive, selected: effectSelected }"
    flat
    bordered
  >
    <q-card-section
      class="cursor-pointer"
      @click="effectActive = !effectActive"
      @mousedown="effectSelected = true"
      @mouseup="effectSelected = false"
      @touchstart="effectSelected = true"
      @touchend="effectSelected = false"
    >
      <div class="row no-wrap items-center justify-between q-gutter-md">
        <q-icon
          name="power_settings_new"
          size="2em"
          :color="effectActive ? 'green-8' : 'red-8'"
        >
        </q-icon>
        <div class="text-bold text-h6">{{ title }}</div>
      </div>
    </q-card-section>
    <q-separator inset />
    <q-card-section class="q-gutter-md">
      <q-select
        filled
        v-model="effectSelection"
        :options="listOfEffects"
        label="Effect"
      />
    </q-card-section>
    <q-separator inset v-if="effectSelection" />
    <q-card-section v-if="effectSelection">
      <slot :effectSelection="effectSelection"></slot>
    </q-card-section>
  </q-card>
</template>

<script setup lang="ts">
import { ref } from 'vue';

const props = defineProps<{
  title: string;
  listOfEffects: string[];
}>();

const effectSelection = ref<string>();
const effectActive = ref<boolean>();
const effectSelected = ref<boolean>();

</script>

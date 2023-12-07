<template>
  <q-layout view="lHh Lpr lFf">
    <div id="background-container">
      <div class="background gradient-color" id="background-gradient" />
      <div class="background gradient-darken" />
    </div>
    <q-header class="text-white" style="background: transparent">
      <q-toolbar class="toolbar" id="toolbar">
        <q-toolbar-title class="">
          <router-link to="/" class="logo-text-link justify-center row">
            <div class="text-h5">🛹 LongLEDBoard ✨</div>
          </router-link>
        </q-toolbar-title>

        <q-btn-dropdown
          flat
          dropdown-icon="eva-chevron-down-outline"
          icon="eva-settings-outline"
          padding="10px"
        >
          <div>
            <div class="column q-pb-sm q-pt-sm">
              <q-btn
                flat
                icon="eva-checkmark-circle-2-outline"
                label="Test Stuff"
                @click="testStuff"
              />
            </div>
          </div>
          <q-separator />
          <div class="column q-pb-sm q-pt-sm">
            <q-btn
              flat
              icon="eva-color-palette-outline"
              label="Rainbow"
              @click="rainbowColors"
            />
            <q-btn
              flat
              :icon="$q.dark.isActive ? 'eva-sun-outline' : 'eva-moon-outline'"
              :label="darkModeText"
              @click="toggleDarkMode"
            />
          </div>
        </q-btn-dropdown>
      </q-toolbar>
    </q-header>

    <q-page-container>
      <router-view />
    </q-page-container>
  </q-layout>
</template>

<script setup lang="ts">
import { ref, ComputedRef, computed } from 'vue';
import { useQuasar } from 'quasar';
import { injectStrict } from 'src/plugins/utils';
import { BackgroundGradientPluginKey } from 'src/types/types';

const $q = useQuasar();

const backgroundGradient = injectStrict(BackgroundGradientPluginKey);

backgroundGradient.setBackgroundGradient('purple');

function toggleDarkMode() {
  $q.dark.toggle();
}

const darkModeText: ComputedRef<string> = computed((): string =>
  $q.dark.isActive ? 'Light Mode' : 'Dark Mode'
);

function testStuff() {
  console.log('test');
}

function rainbowColors() {
  backgroundGradient.setBackgroundGradient('fun');
}
</script>

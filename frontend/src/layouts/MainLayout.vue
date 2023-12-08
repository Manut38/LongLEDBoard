<template>
  <q-layout view="lHh Lpr lFf">
    <div id="background-container">
      <div id="background-gradient" class="background gradient-color" />
      <div class="background gradient-darken" />
    </div>
    <q-header class="text-white" style="background: transparent">
      <q-toolbar id="toolbar" class="toolbar">
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
          <div class="column q-pb-sm q-pt-sm">
            <q-btn
              flat
              icon="eva-settings-outline"
              label="Settings"
              @click="openSettingsDialog"
            />

            <q-btn
              flat
              :icon="$q.dark.isActive ? 'eva-sun-outline' : 'eva-moon-outline'"
              :label="darkModeText"
              @click="$q.dark.toggle()"
            />
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
              icon="eva-cube-outline"
              label="Test Stuff"
              @click="testStuff"
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
import { useQuasar } from 'quasar';
import SettingsDialog from 'src/components/SettingsDialog.vue';

import { injectStrict } from 'src/plugins/utils';
import { useAppConfigStore } from 'src/stores/appConfig';

import { BackgroundGradientPluginKey } from 'src/types/types';
import { ComputedRef, computed, watch } from 'vue';

const $q = useQuasar();

const backgroundGradient = injectStrict(BackgroundGradientPluginKey);
const appConfig = useAppConfigStore();

backgroundGradient.setBackgroundGradient('purple');

watch(
  () => $q.dark.isActive,
  (val) => {
    appConfig.darkMode = val;
  }
);

const darkModeText: ComputedRef<string> = computed((): string =>
  $q.dark.isActive ? 'Light Mode' : 'Dark Mode'
);

function testStuff() {
  console.log('test');
}
function openSettingsDialog() {
  $q.dialog({ component: SettingsDialog, persistent: true });
}

function rainbowColors() {
  backgroundGradient.setBackgroundGradient('fun');
}
</script>

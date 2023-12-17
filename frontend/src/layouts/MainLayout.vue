<template>
  <q-layout view="lhh Lpr lFf">
    <div id="background-container">
      <!-- <div id="background-gradient" class="background gradient-color" /> -->
      <!-- <div class="background gradient-darken" /> -->
      <div class="shape1"></div>
      <div class="shape2"></div>
    </div>
    <q-header class="text-white" style="background: transparent">
      <q-toolbar id="toolbar" class="toolbar">
        <q-toolbar-title class="">
          <router-link to="/" class="logo-text-link justify-center row no-wrap">
            <div class="logo-text-gradient" style="margin-right: 0.5rem">
              🛹
            </div>
            <div>Long</div>
            <div class="logo-text-gradient">LED</div>
            <div>Board</div>
          </router-link>
        </q-toolbar-title>
        <q-spinner v-if="!backend.connected.value" size="1.5em"></q-spinner>
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
            <q-btn
              flat
              icon="eva-browser-outline"
              label="Test Page"
              to="/test"
            />
          </div>
        </q-btn-dropdown>
      </q-toolbar>
    </q-header>

    <q-page-container>
      <router-view v-slot="{ Component }">
        <transition name="slide-right" mode="out-in">
          <component :is="Component" />
        </transition>
      </router-view>
    </q-page-container>
  </q-layout>
</template>

<script setup lang="ts">
import { useQuasar } from 'quasar';
import SettingsDialog from 'src/components/SettingsDialog.vue';

import { injectStrict } from 'src/plugins/utils';
import { useAppConfigStore } from 'src/stores/appConfig';

import { useBackend } from 'src/composables/backend';
import { BackgroundGradientPluginKey } from 'src/types/types';
import { ComputedRef, computed, watch } from 'vue';

const $q = useQuasar();

const backgroundGradient = injectStrict(BackgroundGradientPluginKey);
const appConfig = useAppConfigStore();
const backend = useBackend();

// backgroundGradient.setBackgroundGradient('purple');

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

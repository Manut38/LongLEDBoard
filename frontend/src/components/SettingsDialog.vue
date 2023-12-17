<template>
  <q-dialog ref="dialogRef" @hide="onDialogHide">
    <q-card
      class="q-dialog-plugin"
      :class="$q.dark.isActive ? 'q-dialog-plugin--dark' : ''"
    >
      <q-card-section class="q-dialog__title">Settings</q-card-section>
      <q-card-section>
        <q-input
          v-model="socketBackendURL"
          label="Board Socket Address"
          stack-label
          prefix="ws://"
          autofocus
        />
      </q-card-section>
      <q-card-actions align="right">
        <q-btn flat color="primary" label="SAVE" @click="onOKClick" />
      </q-card-actions>
    </q-card>
  </q-dialog>
</template>

<script setup lang="ts">
import { useDialogPluginComponent } from 'quasar';
import { useAppConfigStore } from 'src/stores/appConfig';
import { ref } from 'vue';

const appConfig = useAppConfigStore();

const socketBackendURL = ref<string>(
  appConfig.socketBackendURL.replace('ws://', '')
);

const props = defineProps({});

defineEmits([
  // REQUIRED; need to specify some events that your
  // component will emit through useDialogPluginComponent()
  ...useDialogPluginComponent.emits,
]);

const { dialogRef, onDialogHide, onDialogOK, onDialogCancel } =
  useDialogPluginComponent();
// dialogRef      - Vue ref to be applied to QDialog
// onDialogHide   - Function to be used as handler for @hide on QDialog
// onDialogOK     - Function to call to settle dialog with "ok" outcome
//                    example: onDialogOK() - no payload
//                    example: onDialogOK({ /*...*/ }) - with payload
// onDialogCancel - Function to call to settle dialog with "cancel" outcome

// this is part of our example (so not required)
function onOKClick() {
  appConfig.socketBackendURL = `ws://${socketBackendURL.value}`;

  // on OK, it is REQUIRED to
  // call onDialogOK (with optional payload)
  onDialogOK();
  // or with payload: onDialogOK({ ... })
  // ...and it will also hide the dialog automatically
}
</script>

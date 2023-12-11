import { useWebSocket, watchIgnorable } from '@vueuse/core';
import { storeToRefs } from 'pinia';
import { QNotifyUpdateOptions, useQuasar } from 'quasar';
import { useAppConfigStore } from 'src/stores/appConfig';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { ISocketResponse } from 'src/types/types';
import { watch } from 'vue';

export function useBackend() {
  const q = useQuasar();
  const appConfig = useAppConfigStore();
  const effectConfig = useEffectConfigStore();

  const { socketBackendURL } = storeToRefs(appConfig);
  const { boardEffectState, previewData } = storeToRefs(effectConfig);

  let errorNotify: (props?: QNotifyUpdateOptions) => void;
  let errorNotifyShown: boolean;

  const { status, data, send, open, close } = useWebSocket(socketBackendURL, {
    autoReconnect: {
      delay: 2000,
    },
    onConnected: () => {
      console.log('Websocket connected.');
      if (errorNotify) {
        errorNotify(); // Dismiss notify
        q.notify({
          color: 'positive',
          message: 'Board reconnected.',
          icon: 'eva-checkmark-circle-2-outline',
          position: 'bottom',
          timeout: 2000,
        });
      }
      errorNotifyShown = false;
    },
    onError: () => {
      if (!errorNotifyShown) {
        errorNotify = q.notify({
          color: 'negative',
          message: 'Board connection failed. Reconnecting...',
          icon: 'eva-alert-circle-outline',
          position: 'bottom',
          timeout: 0,
        });
        errorNotifyShown = true;
      }
    },
  });

  watch(data, (data: string) => {
    try {
      const response: ISocketResponse = JSON.parse(data);
      ignoreBoardEffectStateUpdates(() => {
        if (response.state) {
          console.log('Received Board State:', response);
          boardEffectState.value = response.state;
        }
      });

      if (response.previewData) {
        previewData.value = response.previewData;
      }
    } catch (SyntaxError) {
      throw `Malformed JSON received:\n${data}`;
    }
  });

  const { ignoreUpdates: ignoreBoardEffectStateUpdates } = watchIgnorable(
    boardEffectState,
    (state) => {
      const msg: ISocketResponse = {
        state: state,
      };
      console.log('Sending Board State:', msg);
      send(JSON.stringify(msg));
    },
    {
      deep: true,
    }
  );

  return { status, data, send };
}

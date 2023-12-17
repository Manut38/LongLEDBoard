import { useWebSocket, watchIgnorable } from '@vueuse/core';
import { storeToRefs } from 'pinia';
import { Notify, QNotifyUpdateOptions } from 'quasar';
import { useAppConfigStore } from 'src/stores/appConfig';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { ISocketResponse } from 'src/types/types';
import { computed, watch } from 'vue';

const appConfig = useAppConfigStore();
const effectConfig = useEffectConfigStore();

const { socketBackendURL } = storeToRefs(appConfig);
const { boardEffectState, previewData } = storeToRefs(effectConfig);

let errorNotify: (props?: QNotifyUpdateOptions) => void;
let errorNotifyShown: boolean;

const { status, data, send, open, close } = useWebSocket(socketBackendURL, {
  autoReconnect: {
    delay: 5000,
  },
  onConnected: () => {
    console.log('Websocket connected.');
    if (errorNotify) {
      errorNotify(); // Dismiss notify
      Notify.create({
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
      errorNotify = Notify.create({
        color: 'negative',
        message: 'Board connection failed',
        icon: 'eva-alert-circle-outline',
        position: 'bottom',
        timeout: 3000,
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
    if (connected.value) {
      const msg: ISocketResponse = {
        state: state,
      };
      console.log('Sending Board State:', msg);
      send(JSON.stringify(msg));
    }
  },
  {
    deep: true,
  }
);

export const connected = computed(() => status.value === 'OPEN');

// export default boot(({ app, store }) => {});

export { close, data, open, send, status };

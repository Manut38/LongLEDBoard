import { useThrottleFn, useWebSocket } from '@vueuse/core';
import { storeToRefs } from 'pinia';
import { Notify, QNotifyUpdateOptions } from 'quasar';
import { useAppConfigStore } from 'src/stores/appConfig';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import {
  BoardStateMsg,
  EffectConfigMsg,
  ISocketResponse,
} from 'src/types/types';
import { computed } from 'vue';

const appConfig = useAppConfigStore();
const effectConfig = useEffectConfigStore();

const { socketBackendURLFull } = storeToRefs(appConfig);
const {
  boardState,
  previewData,
  bgEffectConfig,
  accelEffectConfig,
  steeringEffectConfig,
} = storeToRefs(effectConfig);

let errorNotify: (props?: QNotifyUpdateOptions) => void;
let errorNotifyShown: boolean;

const { status, data, send, open, close } = useWebSocket(socketBackendURLFull, {
  autoReconnect: {
    delay: 1000,
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
  onDisconnected: () => {
    console.log('Websocket disconnected.');
    if (errorNotify) {
      errorNotify(); // Dismiss notify
      Notify.create({
        color: 'warning',
        message: 'Board disconnectedc.',
        icon: 'eva-checkmark-circle-2-outline',
        position: 'bottom',
        timeout: 2000,
      });
    }
  },
});

const sendEffectConfigState = useThrottleFn(
  (state: EffectConfigMsg) => {
    if (connected.value) {
      const msg: ISocketResponse = {
        effectConfig: state,
      };
      console.log('Sending effectConfig:', msg);
      send(JSON.stringify(msg));
    }
  },
  30,
  true
);

const sendBoardState = useThrottleFn(
  (state: BoardStateMsg) => {
    if (connected.value) {
      const msg: ISocketResponse = {
        state: state,
      };
      console.log('Sending boardState:', msg);
      send(JSON.stringify(msg));
    }
  },
  30,
  true
);

// watchDebounced(
//   data,
//   (data: string) => {
//     try {
//       const response: ISocketResponse = JSON.parse(data);
//       if (response.state) {
//         console.log('Received Board State:', response);
//         boardState.value = response.state;
//       }
//       if (response.effectConfig?.bgEffect) {
//         console.log('Received BgEffectConfig State:', response);
//         bgEffectConfig.value = response.effectConfig.bgEffect;
//       }
//       if (response.effectConfig?.accelEffect) {
//         console.log('Received AccelEffectConfig State:', response);
//         accelEffectConfig.value = response.effectConfig.accelEffect;
//       }

//       if (response.effectConfig?.steeringEffect) {
//         console.log('Received SteeringEffectConfig State:', response);
//         steeringEffectConfig.value = response.effectConfig.steeringEffect;
//       }
//       if (response.previewData) {
//         previewData.value = response.previewData;
//       }
//     } catch (SyntaxError) {
//       throw `Malformed JSON received:\n${data}`;
//     }
//   },
//   { debounce: 30 }
// );

export const connected = computed(() => status.value === 'OPEN');

export function useBackend() {
  return {
    status,
    data,
    send,
    connected,
    sendEffectConfigState,
    sendBoardState,
  };
}

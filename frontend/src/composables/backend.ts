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

let errorNotify: (props?: QNotifyUpdateOptions) => void;
let errorNotifyShown: boolean;

const { status, data, send } = useWebSocket(socketBackendURLFull, {
  autoReconnect: {
    delay: 1000,
  },
  heartbeat: {
    message: 'ping',
    interval: 5000,
    pongTimeout: 2000,
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
    sendCachedConfig();
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
    errorNotify = Notify.create({
      color: 'warning',
      message: 'Board disconnected',
      icon: 'eva-alert-circle-outline',
      position: 'bottom',
      timeout: 2000,
    });
  },
});

const sendEffectConfigState = useThrottleFn(
  (state: EffectConfigMsg) => {
    if (connected.value) {
      const msg: ISocketResponse = {
        effectConfig: state,
      };
      const jsonMsg = JSON.stringify(msg);
      send(jsonMsg);
      console.log('Sent effectConfig:', JSON.parse(jsonMsg));
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
      const jsonMsg = JSON.stringify(msg);
      send(jsonMsg);
      console.log('Sent boardState:', JSON.parse(jsonMsg));
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

function sendCachedConfig() {
  sendEffectConfigState({
    accelEffect: effectConfig.accelEffectConfig,
    bgEffect: effectConfig.bgEffectConfig,
    steeringEffect: effectConfig.steeringEffectConfig,
  });
  sendBoardState(effectConfig.boardState);
  console.log('Sent cached config to board.');
}

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

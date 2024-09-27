import { throttleFilter, useWebSocket, watchIgnorable } from '@vueuse/core';
import { storeToRefs } from 'pinia';
import { Notify, QNotifyUpdateOptions } from 'quasar';
import { useAppConfigStore } from 'src/stores/appConfig';
import { useEffectConfigStore } from 'src/stores/effectConfig';
import { ISocketResponse } from 'src/types/types';
import { computed, watch } from 'vue';

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
    ignoreBoardStateUpdates(() => {
      if (response.state) {
        console.log('Received Board State:', response);
        boardState.value = response.state;
      }
    });
    ignoreBgEffectConfigStateUpdates(() => {
      if (response.effectConfig?.bgEffect) {
        console.log('Received BgEffectConfig State:', response);
        bgEffectConfig.value = response.effectConfig.bgEffect;
      }
    });
    ignoreAccelEffectConfigStateUpdates(() => {
      if (response.effectConfig?.accelEffect) {
        console.log('Received AccelEffectConfig State:', response);
        accelEffectConfig.value = response.effectConfig.accelEffect;
      }
    });
    ignoreSteeringEffectConfigStateUpdates(() => {
      if (response.effectConfig?.steeringEffect) {
        console.log('Received SteeringEffectConfig State:', response);
        steeringEffectConfig.value = response.effectConfig.steeringEffect;
      }
    });
    if (response.previewData) {
      previewData.value = response.previewData;
    }
  } catch (SyntaxError) {
    throw `Malformed JSON received:\n${data}`;
  }
});

const { ignoreUpdates: ignoreBoardStateUpdates } = watchIgnorable(
  boardState,
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
    eventFilter: throttleFilter(50),
    deep: true,
  }
);

const { ignoreUpdates: ignoreBgEffectConfigStateUpdates } = watchIgnorable(
  bgEffectConfig,
  (state) => {
    if (connected.value) {
      const msg: ISocketResponse = {
        effectConfig: {
          bgEffect: state,
        },
      };
      console.log('Sending BgEffectConfig:', msg);
      send(JSON.stringify(msg));
    }
  },
  {
    eventFilter: throttleFilter(50),
    deep: true,
  }
);
const { ignoreUpdates: ignoreAccelEffectConfigStateUpdates } = watchIgnorable(
  accelEffectConfig,
  (state) => {
    if (connected.value) {
      const msg: ISocketResponse = {
        effectConfig: {
          accelEffect: state,
        },
      };
      console.log('Sending AccelEffectConfig:', msg);
      send(JSON.stringify(msg));
    }
  },
  {
    eventFilter: throttleFilter(50),
    deep: true,
  }
);
const { ignoreUpdates: ignoreSteeringEffectConfigStateUpdates } =
  watchIgnorable(
    steeringEffectConfig,
    (state) => {
      if (connected.value) {
        const msg: ISocketResponse = {
          effectConfig: {
            steeringEffect: state,
          },
        };
        console.log('Sending SteeringEffectConfig:', msg);
        send(JSON.stringify(msg));
      }
    },
    {
      eventFilter: throttleFilter(50),
      deep: true,
    }
  );

export const connected = computed(() => status.value === 'OPEN');

// export default boot(({ app, store }) => {});

export { close, data, open, send, status };

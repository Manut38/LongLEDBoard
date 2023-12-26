import { defineStore } from 'pinia';
import { ref } from 'vue';

export const useAppConfigStore = defineStore(
  'appConfig',
  () => {
    const darkMode = ref<boolean>(true);
    const socketBackendURL = ref<string>(getInitialBackendAddress());
    const debugActive = ref<boolean>(false);

    function getInitialBackendAddress(): string {
      return `ws://${window.location.hostname}:3003`;
    }

    return {
      darkMode,
      socketBackendURL,
      debugActive,
    };
  },
  {
    persist: true,
  }
);

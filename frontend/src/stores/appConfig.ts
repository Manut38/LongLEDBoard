import { defineStore } from 'pinia';
import { computed, ref } from 'vue';

export const useAppConfigStore = defineStore(
  'appConfig',
  () => {
    const darkMode = ref<boolean>(true);
    const socketBackendURL = ref<string>(getInitialBackendAddress());
    const socketBackendURLFull = computed(() => socketBackendURL.value + '/ws');
    const debugActive = ref<boolean>(false);

    function getInitialBackendAddress(): string {
      return `ws://${window.location.hostname}:3003`;
    }

    return {
      darkMode,
      socketBackendURL,
      socketBackendURLFull,
      debugActive,
    };
  },
  {
    persist: true,
  }
);

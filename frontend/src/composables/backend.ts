import { connected, data, send, status } from 'src/boot/backend';

export function useBackend() {
  return { status, data, send, connected };
}

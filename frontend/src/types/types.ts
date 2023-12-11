import { InjectionKey } from 'vue';

export interface BackgroundGradient {
  setBackgroundGradient: (cssClass: string) => void;
}

export const BackgroundGradientPluginKey: InjectionKey<BackgroundGradient> =
  Symbol('BackgroundGradient Plugin');

export interface ISocketResponse {
  previewData?: PreviewData;
  state?: BoardEffectState;
}

export interface PreviewData {
  pixeldata: PixelData[];
}

export interface PixelData {
  r: number;
  g: number;
  b: number;
}

export interface BoardEffectState {
  active: boolean;
  bg_active: boolean;
  accel_active: boolean;
  steering_active: boolean;
}

import { InjectionKey } from 'vue';

export interface BackgroundGradient {
  setBackgroundGradient: (cssClass: string) => void;
}

export const BackgroundGradientPluginKey: InjectionKey<BackgroundGradient> =
  Symbol('BackgroundGradient Plugin');

import { InjectionKey } from 'vue';
export interface BackgroundGradient {
  setBackgroundGradient: (cssClass: string) => void;
}
export const BackgroundGradientPluginKey: InjectionKey<BackgroundGradient> =
  Symbol('BackgroundGradient Plugin');
export interface ISocketResponse {
  previewData?: PreviewData;
  state?: BoardEffectState;
  effectConfig?: EffectConfigState;
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
  bgActive: boolean;
  bgSelected: BgEffect;
  accelActive: boolean;
  accelSelected: AccelEffect;
  steeringActive: boolean;
  steeringSelected: SteeringEffect;
}
export interface EffectConfigState {
  bgEffect?: BackgroundEffectConfig;
  accelEffect?: AccelEffectConfig;
  steeringEffect?: SteeringEffectConfig;
}

export enum BgEffect {
  Solid = 'solid',
  Fire = 'fire',
  ColorFade = 'color_fade',
  ColorChase = 'color_chase',
  Breathing = 'breathing',
  Sparkle = 'sparkle',
}

export enum AccelEffect {
  ColorStrike = 'color_strike',
  RainbowStrike = 'rainbow_strike',
  GradientStrike = 'gradient_strike',
  Strobe = 'strobe',
  RainbowStrobe = 'rainbow_strobe',
  ColorChase = 'color_chase',
}

export enum SteeringEffect {
  ColorFadeLeftRight = 'color_fade_left_right',
  Water = 'water',
}

export interface EffectListEntry {
  label: string;
  id: string;
}

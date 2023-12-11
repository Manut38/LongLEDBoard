import { InjectionKey } from 'vue';
export interface BackgroundGradient {
  setBackgroundGradient: (cssClass: string) => void;
}
export const BackgroundGradientPluginKey: InjectionKey<BackgroundGradient> =
  Symbol('BackgroundGradient Plugin');
export interface ISocketResponse {
  previewData?: PreviewData;
  state?: BoardEffectState;
  effectConfig?: EffectConfig;
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
export interface EffectConfig {
  bgEffect?: BackgroundEffectConfig;
  accelEffect?: AccelEffectConfig;
  steeringEffect?: SteeringEffectConfig;
}

export enum BgEffect {
  Solid = 'solid',
  Fire = 'fire',
  ColorFade = 'colorfade',
  ColorChase = 'colorchase',
  Breathing = 'breathing',
  sparkle = 'sparkle',
}

export enum AccelEffect {
  ColorStrike = 'colorstrike',
  RainbowStrike = 'rainbowstrike',
  GradientStrike = 'gradientstrike',
  Strobe = 'strobe',
  RainbowStrobe = 'rainbowstrobe',
  ColorChase = 'colorchase',
}

export enum SteeringEffect {
  ColorRightLeft = 'colorrightleft',
  Water = 'water',
}

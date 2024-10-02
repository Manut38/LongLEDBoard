export interface SolidColorEffectConfig {
  color: string;
}
export interface RainbowEffectConfig {
  duration: number;
}
export interface ColorFadeEffectConfig {
  colors: string[];
  time: number;
}
export interface ColorChaseEffectConfig {
  colors: string[];
  time: number;
}
export interface BreathingEffectConfig {
  colors: string[];
  time: number;
}
export interface FireEffectConfig {
  speed: number;
}
export interface SparkleEffectConfig {
  background: string;
  sparkleColor: string;
  speed: number;
}
export interface ColorStrikeEffectConfig {
  color: string;
  duration: number;
}
export interface RainbowStrikeEffectConfig {
  duration: number;
}
export interface GradientStrikeEffectConfig {
  colors: string[];
  duration: number;
}
export interface StrobeEffectConfig {
  color: string;
  speed: number;
}
export interface RainbowStrobeEffectConfig {
  speed: number;
}
export interface ColorFadeTiltEffectConfig {
  colors: string[];
}
export interface WaterEffectConfig {
  gravity: number;
}

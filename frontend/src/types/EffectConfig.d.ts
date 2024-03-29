export interface SolidColorEffectConfig {
  color: string;
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
  speed: number;
}
export interface RainbowStrikeEffectConfig {
  speed: number;
}
export interface GradientStrikeEffectConfig {
  colors: string[];
  speed: number;
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

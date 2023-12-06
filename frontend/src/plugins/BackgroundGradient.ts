import { nextTick, Plugin } from 'vue';
import { BackgroundGradientPluginKey } from 'src/types/types';

export const BackgroundGradient: Plugin = {
  install: (app, options) => {
    let transitionTimer: NodeJS.Timeout;

    app.provide(BackgroundGradientPluginKey, {
      setBackgroundGradient: (cssClass: string) => {
        nextTick(() => {
          // Reset Timer //
          clearTimeout(transitionTimer);

          const gradientDiv = getGradientDiv();

          // Create new transition div //
          const newTransition = document.createElement('div');
          newTransition.classList.value = `${options.backgroundBaseClass} ${options.customGradientClass} ${cssClass} ${options.transitionClass}`;
          newTransition.style.zIndex = (
            parseInt(getComputedStyle(gradientDiv).zIndex) +
            gradientDiv.children.length +
            1
          ).toString();

          // Append new div //
          gradientDiv.appendChild(newTransition);

          // Set timer delete all transition divs when animation finishes //
          const animDuration =
            parseInt(getComputedStyle(newTransition).animationDuration) * 1000;
          transitionTimer = setTimeout(() => {
            // Set background gradient to new color //
            gradientDiv.classList.value = `${options.backgroundBaseClass} ${options.customGradientClass} ${cssClass}`;

            // Restart background animation //
            gradientDiv.style.animation = 'none';
            setTimeout(() => (gradientDiv.style.animation = ''), 100);

            // Remove transition divs //
            while (gradientDiv.firstChild) {
              gradientDiv.removeChild(gradientDiv.firstChild);
            }
          }, animDuration);
        });
      },
    });

    function getGradientDiv(): HTMLElement {
      const gradientDiv = document.getElementById(options.gradientDivID);
      if (!gradientDiv) {
        throw new Error(
          `BackgroundGradient: Missing gradient div (${options.gradientDivID})`
        );
      }
      return gradientDiv;
    }
  },
};

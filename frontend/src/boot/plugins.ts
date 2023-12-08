import { boot } from 'quasar/wrappers';
import { BackgroundGradient } from 'src/plugins/BackgroundGradient';
import store from 'src/stores/index';

export default boot(({ app }) => {
  app.use(BackgroundGradient, {
    backgroundBaseClass: 'background',
    gradientDivID: 'background-gradient',
    customGradientClass: 'gradient-color',
    transitionClass: 'transition',
  });

  app.use(store);
});

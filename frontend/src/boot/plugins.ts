import { boot } from 'quasar/wrappers';
import { BackgroundGradient } from 'src/plugins/BackgroundGradient';

export default boot(({ app }) => {
  app.use(BackgroundGradient, {
    backgroundBaseClass: 'background',
    gradientDivID: 'background-gradient',
    customGradientClass: 'gradient-color',
    transitionClass: 'transition',
  });

});

import { ThemeDefinition, createVuetify } from 'vuetify';
import { VColorPicker } from 'vuetify/components/VColorPicker';

const customDarkTheme: ThemeDefinition = {
  dark: true,
  colors: {
    surface: '#1D1D1D',
    primary: '#f66244',
    secondary: '#FFA726',
  },
};

const vuetify = createVuetify({
  components: {
    VColorPicker,
  },
  theme: {
    defaultTheme: 'customDarkTheme',
    themes: { customDarkTheme },
  },
});

export default vuetify;

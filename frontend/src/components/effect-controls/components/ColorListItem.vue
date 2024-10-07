<!-- ColorPickerList.vue -->
<template>
  <q-expansion-item
    dense
    :duration="200"
    header-style="border-radius: 8px;"
  >
    <template #header>
      <q-item-section style="text-align: center;">{{ label }}</q-item-section>
    </template>
    <div class="q-gutter-y-md q-px-sm">
      <q-tabs
        v-model="activeTab"
        dense
        active-color="primary"
        indicator-color="primary"
        align="center"
        narrow-indicator
        inline-label
        :breakpoint="0"
      >
      <q-btn
          v-if="localColors.at(activeTab)"
          flat
          round
          icon="eva-trash-2-outline"
          @click="removeColor(activeTab)"
        />
        <q-tab
          v-for="color in localColors"
          :key="color.id"
          :name="color.id"
          style="
            max-height: 40px;
            max-width: 40px;
            border-radius: 50%;
            opacity: 1;
          "
        >
          <q-avatar size="sm" :style="{ backgroundColor: color.color }">
          </q-avatar>
        </q-tab>
        <q-btn flat round icon="eva-plus-outline" @click="addColor" />

      </q-tabs>

      <div v-if="localColors.at(activeTab)" class="row justify-center">
        <v-color-picker
          v-model="localColors[activeTab].color"
          flat
          hide-inputs
          mode="hex"
          show-swatches
          width="250"
          swatches-max-height="100"
          @update:model-value="updateColor(activeTab, $event)"
        ></v-color-picker>
      </div>
    </div>
  </q-expansion-item>
</template>

<script setup lang="ts">
import { computed, ref, watch } from 'vue';

interface ColorItem {
  id: number;
  color: string;
}

const props = defineProps<{
  label: string;
  modelValue: string[]; // Array of hex codes
}>();

const emit = defineEmits(['update:modelValue']);

const colors = ref<ColorItem[]>(
  props.modelValue.map((color, index) => ({
    id: index,
    color,
  }))
);

const activeTab = ref(colors.value[0]?.id || 0);

const localColors = computed({
  get: () => colors.value,
  set: (newValue) => {
    colors.value = newValue;
    // Emit updated color hex codes to the parent
    emit(
      'update:modelValue',
      colors.value.map((c) => c.color)
    );
  },
});

// Watch for changes in `modelValue` and update the colors accordingly
watch(
  () => props.modelValue,
  (newModelValue) => {
    colors.value = newModelValue.map((color, index) => ({
      id: index,
      color,
    }));
  }
);

// Update an existing color
const updateColor = (index: number, newColor: string) => {
  colors.value[index].color = newColor;
  // Trigger the computed setter to emit the change
  localColors.value = [...colors.value]; // Ensure reactivity
};

// Add a new color
const addColor = () => {
  const newId =
    Math.max(0, ...colors.value.map((c) => c.id)) +
    (colors.value.length > 0 ? 1 : 0);
  colors.value.push({
    id: newId,
    color: colors.value.at(activeTab.value)?.color || '#FF0000', // Default to red
  });
  console.log(newId);
  activeTab.value = newId;
  // Trigger the computed setter to emit the change
  localColors.value = [...colors.value];
};

// Remove a color
const removeColor = (index: number) => {
  const removedId = colors.value[index].id;
  colors.value.splice(index, 1);
  if (activeTab.value === removedId) {
    activeTab.value = colors.value[removedId - 1]?.id || 0;
  }
  // Trigger the computed setter to emit the change
  localColors.value = [...colors.value];
};
</script>

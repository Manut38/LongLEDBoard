<template>
  <q-card
    class="effect-control-card"
    :class="{ active: active, selected: effectSelected }"
    bordered
    :flat="!q.dark.isActive"
  >
    <q-card-section
      class="cursor-pointer"
      @click="$emit('toggleActive')"
      @mousedown="effectSelected = true"
      @mouseup="effectSelected = false"
      @touchstart="effectSelected = true"
      @touchend="effectSelected = false"
    >
      <div class="row no-wrap items-center justify-left q-gutter-md">
        <div class="col-grow" @mousedown.stop @touchstart.stop @click.stop>
          <q-select
            v-model="effectSelection"
            dense
            filled
            :options="listOfEffects"
            :label="title"
            transition-show="jump-down"
            transition-hide="jump-up"
          />
        </div>
        <q-icon
          :name="
            active
              ? 'eva-checkmark-circle-2-outline'
              : 'eva-pause-circle-outline'
          "
          size="2em"
          :color="active ? 'light-green-7' : 'grey-7'"
        >
        </q-icon>
      </div>
    </q-card-section>
    <q-separator v-if="effectSelection" inset />
    <q-card-section v-if="effectSelection">
      <slot :effect-selection="effectSelection"></slot>
    </q-card-section>
  </q-card>
</template>

<script setup lang="ts">
import { useQuasar } from 'quasar';
import { ref } from 'vue';

const props = defineProps<{
  title: string;
  listOfEffects: string[];
  active: boolean;
}>();

const q = useQuasar();

defineEmits(['toggleActive']);

const effectSelection = ref<string>();
const effectSelected = ref<boolean>();
</script>

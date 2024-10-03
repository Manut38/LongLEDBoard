<template>
  <q-card
    class="effect-control-card"
    :class="{ active: active, selected: headerPressed }"
    bordered
    :flat="!q.dark.isActive"
  >
    <q-card-section
      class="cursor-pointer"
      @click="$emit('toggleActive')"
      @mousedown="headerPressed = true"
      @mouseup="headerPressed = false"
      @touchstart="headerPressed = true"
      @touchend="headerPressed = false"
    >
      <div class="row no-wrap items-center justify-left q-gutter-md">
        <div class="col-grow" @mousedown.stop @touchstart.stop @click.stop>
          <q-select
            v-model="selectedEntryModel"
            dense
            filled
            :options="effectList"
            :label="title"
            transition-show="jump-down"
            transition-hide="jump-up"
            @update:model-value="(selected: EffectListEntry) => $emit('changeSelection', selected.id)"
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
    <q-separator v-if="selectedEntryModel" inset />
    <q-card-section v-if="selectedEntryModel">
      <q-slide-transition>
        <slot :selected="selectedEntryModel"></slot>
      </q-slide-transition>
    </q-card-section>
  </q-card>
</template>

<script setup lang="ts">
import { useQuasar } from 'quasar';
import { EffectListEntry } from 'src/types/types';
import { ref, watch } from 'vue';

const props = defineProps<{
  title: string;
  effectList: EffectListEntry[];
  active: boolean;
  selectedId: string;
}>();

defineEmits(['toggleActive', 'changeSelection']);
const selectedEntryModel = ref<EffectListEntry>();
const headerPressed = ref<boolean>();
const q = useQuasar();

watch(
  () => props.selectedId,
  (id) => {
    setSelectionFromId(id);
  }
);

function setSelectionFromId(id: string) {
  selectedEntryModel.value = props.effectList.find((entry) => entry.id === id);
}

// Set inital entry
setSelectionFromId(props.selectedId);
</script>

<template>
	<q-expansion-item dense>
	      <template #header>
	        <q-item-section avatar>
	          <q-avatar
	            :style="{
	              backgroundColor: color,
	            }"
	          />
	        </q-item-section>
	        <q-item-section>Color</q-item-section>
	      </template>
	      <div class="row justify-center">
	        <v-color-picker
	          v-model="colorRef"
	          class="q-my-sm"
	          flat
	          hide-inputs
	          mode="rgb"
	          show-swatches
	          width="260"
	          swatches-max-height="100"
	          @update:model-value="$emit('colorChanged', colorRef)"
	          @mousedown.stop
	          @touchstart.stop
	          @click.stop
	        ></v-color-picker>
	      </div>
	    </q-expansion-item>
</template>

<script setup lang="ts">
import { ref } from 'vue';

const props = defineProps<{
  color: string;
}>();

defineEmits(['colorChanged']);

const colorRef = ref(props.color);

</script>

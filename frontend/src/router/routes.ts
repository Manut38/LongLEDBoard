import { RouteRecordRaw } from 'vue-router';

const routes: RouteRecordRaw[] = [
  {
    path: '/',
    component: () => import('layouts/MainLayout.vue'),
    children: [
      {
        path: '',
        redirect: 'control',
      },
      {
        path: 'control',
        name: 'control',
        component: () => import('pages/ControlPage.vue'),
      },
      {
        path: 'presets',
        name: 'presets',
        component: () => import('pages/PresetsPage.vue'),
      },
      { path: '/test', component: () => import('pages/TestPage.vue') },
    ],
  },

  // Always leave this as last one,
  // but you can also remove it
  {
    path: '/:catchAll(.*)*',
    component: () => import('pages/ErrorNotFound.vue'),
  },
];

export default routes;

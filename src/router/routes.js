
const routes = [
  {
    path: '/',
    component: () => import('layouts/MyLayout.vue'),
    children: [
      { path: '', component: () => import('pages/Index.vue'), meta: { requiresAuth: true }  } , 
      { path: '/clientes', component: () => import('pages/clientes/lista.vue') },
      { path: '/clientes/form/:id', name: 'clienteForm', component: () => import('pages/clientes/form.vue')},
      { path: '/login', name: 'login', component: () => import('pages/login.vue')},
      { path: '/pedidos/form/:id', component:()=>import('pages/pedidos/form.vue')},
    ],
  },
];

// Always leave this as last one
if (process.env.MODE !== 'ssr') {
  routes.push({
    path: '*',
    component: () => import('pages/Error404.vue'),
  });
}

export default routes;

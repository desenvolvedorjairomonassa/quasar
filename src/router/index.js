import Vue from 'vue';
import VueRouter from 'vue-router';
import VueResource from 'vue-resource';
import routes from './routes';
import store from '../store/index';
import Vuelidate from 'vuelidate';

Vue.use(Vuelidate)
Vue.use(VueRouter);
Vue.use(VueResource);

Vue.http.options.root = process.env.API

//Vue.router = router;


export default function (/* { store, ssrContext } */) {
  const Router = new VueRouter({
    scrollBehavior: () => ({ y: 0 }),
    routes,
    store,
    // Leave these as is and change from quasar.conf.js instead!
    // quasar.conf.js -> build -> vueRouterMode
    mode: process.env.VUE_ROUTER_MODE, 
    base: process.env.VUE_ROUTER_BASE,
  });

  return Router;
}

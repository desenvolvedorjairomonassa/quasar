<template>
  <q-layout view="lHh Lpr lFf">
    <q-layout-header>
      <q-toolbar
        color="info"
        :glossy="$q.theme === 'mat'"
        :inverted="$q.theme === 'ios'"
      >
        <q-btn
          flat
          dense
          round
          @click="miniState=!miniState;  "
          aria-label="Menu"
        >
          <q-icon name="menu" />
        </q-btn>

        <q-toolbar-title
         color="info"
        >
          Jairo Monassa App 
          <div slot="subtitle"> usuario </div>
        </q-toolbar-title>
      </q-toolbar>
    </q-layout-header>

    <q-layout-drawer 
      v-model="leftDrawerOpen"
      :mini = "miniState"
      :content-class="$q.theme === 'mat' ? 'bg-info' : null"
    >
      <q-list
        no-border
        link        
        inset-delimiter
      >
        <q-list-header>Menu</q-list-header>
        <q-item to="/clientes">
          <q-item-side color=white icon="person" />
          <q-item-main text-color=white label="Clientes" sublabel="cadastro de clientes" />
        </q-item>
        <q-item to="/Vendedor">
          <q-item-side color=white icon="person" />
          <q-item-main text-color=white label="Vendedor" sublabel="cadastro de vendedor" />
        </q-item>  
        <q-item to="/banco">
          <q-item-side color=white icon="fas fa-money-check-alt" />
          <q-item-main text-color=white label="banco" sublabel="cadastro de banco" />
        </q-item>  
        <q-item to="/pedidos/form/0">
          <q-item-side color=white icon="store" />
          <q-item-main text-color=white label="pedido" sublabel="registro de pedido" />
        </q-item>  
        <q-item to="/pedido/forms/0">
          <q-item-side color=white icon="credit_card" />
          <q-item-main text-color=white label="Cartão" sublabel="cartão de credito" />
        </q-item>  
        <q-item to="/pedido">
          <q-item-side color=white icon="library_books" />
          <q-item-main text-color=white label="Boletos" sublabel="" />
        </q-item>
        <q-item to="/pedido">
          <q-item-side color=white icon="assignment_return" />
          <q-item-main text-color=white label="Remessa" sublabel="" />
        </q-item>
        <q-item to="/pedido">
          <q-item-side color=white icon="assignment_returned" />
          <q-item-main text-color=white label="Retorno" sublabel="retorno" />
        </q-item>                       
        <q-item to="/pedido">
          <q-item-side color=white icon="local_post_office" />
          <q-item-main text-color=white label="Mala" sublabel="" />
        </q-item>
        <q-item to="/pedido">
          <q-item-side color=white icon="event" />
          <q-item-main text-color=white label="Agenda" sublabel="" />
        </q-item>  

        <q-item to="/pedido">
          <q-item-side color=white icon="payment" />
          <q-item-main text-color=white label="Receita" sublabel="" />
        </q-item>  
        <q-item to="/pedido">
          <q-item-side color=white icon="grade" />
          <q-item-main text-color=white label="Receita" sublabel="" />
        </q-item>          

      </q-list>
    </q-layout-drawer>

    <q-page-container>
      <router-view />
    </q-page-container>
  </q-layout>
</template>

<script>
import { openURL } from 'quasar';
import { Store } from 'vuex';

export default {
  name: 'MyLayout',
  usuarioLogado : Store.usuarioLogado ,
  
  data() {

    return {
      
      leftDrawerOpen: this.$q.platform.is.desktop,
       miniState: false
    };
  },
  methods: {
    openURL,

  }
};
</script>

<style>
</style>

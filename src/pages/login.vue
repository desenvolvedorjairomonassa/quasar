<template>
  <q-page padding >
    <div class="fundo" inset-shadow >
      <form action="#" @submit.prevent="login">
      <q-input class='input-login'
       
       v-model="username" type="text" float-label="usuário/email" color="white" autofocus="true"/>
      <div style="clear:both;">&nbsp;</div>
      <q-input class='input-login'
       v-model="password" float-label="senha" type="password" color="white" />
       <div style="clear:both;">&nbsp;</div>
        <div style="clear:both;">&nbsp;</div>
      <q-btn type="submit"  :disabled="loading" >Login</q-btn>
      <br>
      <div v-if="successMessage" class="success-message">{{ successMessage }}</div>
      <div v-if="serverError" style="text-red" class="server-error">{{ serverError }}</div>      
      </form>
    </div>
  </q-page>
</template>

<script>
import {store} from '../store/index.js';
import { required, minLength, between } from 'vuelidate/lib/validators'

export default {
  name : 'login',
  props: {
    dataSuccessMessage: {
      type: String,
    }
  },
  validations: {
    username: {required},
    password: {required}
  } , 
  computed : {
    EValido () {

      return !this.$v.username.$invalid && !this.$v.password.$invalid
    }
  },
  data() {
    return {
        username: '',
        password: '',
        serverError: '',
        errorretorno : '',
        successMessage: this.dataSuccessMessage,
        loading: false,  
    }
  } ,
  methods: {
    mounted() {
      this.name = ''
      this.password = ''

    },
    login() {
       
        if (!this.EValido) {
           this.serverError = 'Usuário e senha não preenchido'; 
          return false
          
        }
        
        if ( !this.username || !this.password)  {
          this.serverError = 'Usuário e senha não preenchido';
          return false;
        }
        this.loading = true;
        
        this.$store.dispatch('acessoToken', {
          
          username: this.username,
          password: this.password,
        })
        .then(response => {
          this.loading = false
          console.log(response)
         // this.$router.push({ name: 'todo' })
        })
        .catch(error => {
         
          console.log('falha')
          localStorage.removeItem('access_token')
          if (error.response.data.error.statusCode == 401) {
            this.serverError  = 'Falha no login'
          }
          else 
           {
            this.serverError = error.response.data
           }
          
          this.loading = false
          this.username = ''
          this.password = ''
          this.successMessage = ''
        }) 
     
      }
  }
}
</script>

<style>

.input-login { 
  float:left;
  width:400px;
  margin-left : 50px; 
  margin-top: 25px;
}

.invalido {
  border-bottom: red 1px solid;
  
}

.fundo{

      width: 500px;
      height: 300px;
      
      text-align:center;
      background-color:rgb(81, 133, 133);
      color: white;
      
      /* pura mágica */
      position: absolute;
      top: 30%; /* posiciona na metade da tela */
      left: 30%;
      margin-top: -35px; /* e retrocede metade da altura */    
}
</style>

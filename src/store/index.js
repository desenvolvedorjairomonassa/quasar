import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios';
import Vuelidate from 'vuelidate';

//import example from './storemob';

Vue.use(Vuex);
Vue.use(Vuelidate);
//axios.defaults.baseURL = 'http://localhost:8080/api/Users/'

const Store = new Vuex.Store({
  data: {
    usuarioLogado : localStorage.getItem('usuarioLogado') || null,
  },
  state: {
    token: localStorage.getItem('access_token') || null,
    
    
  },
  getters: {
    loggedIn(state) {
      return state.token !== null
    }
   
  },
  mutations: {
    
    acessoToken(state, token) {
      state.token = token
    },
    destroyToken(state) {
      state.token = null
    },
   
  },
  actions: {
    retrieveName(context) {
      axios.defaults.headers.common['Authorization'] = 'Bearer ' + context.state.token

      return new Promise((resolve, reject) => {
        axios.get('/user')
          .then(response => {
            resolve(response)
          })
          .catch(error => {
            reject(error)
          })
      })
    },
    
    register(context, data) {
      return new Promise((resolve, reject) => {
        axios.post('/register', {
          name: data.name,
          email: data.email,
          password: data.password,
        })
          .then(response => {
            resolve(response)
          })
          .catch(error => {
            reject(error)
          })
      })
    },
    destroyToken(context) {
      axios.defaults.headers.common['Authorization'] = 'Bearer ' + context.state.token

      if (context.getters.loggedIn) {
        return new Promise((resolve, reject) => {
          axios.post('/logout')
            .then(response => {
              localStorage.removeItem('access_token')
              context.commit('destroyToken')
              resolve(response)
              // console.log(response);
              // context.commit('addTodo', response.data)
            })
            .catch(error => {
              localStorage.removeItem('access_token')
              context.commit('destroyToken')
              reject(error)
            })
        })
      }
    },
    acessoToken(context, credentials) {

      return new Promise((resolve, reject) => {
        axios.post('http://localhost:3000/api/Users/login', {
          username: credentials.username,
          password: credentials.password,
        })
          .then(response => {
            const token = response.data.id //access_token
            //response.data.access_token
            localStorage.setItem('access_token', token)
            localStorage.setItem('usuarioLogado',credentials.username)
            context.commit('acessoToken', token)
            resolve(response)
            // console.log(response);
            // context.commit('addTodo', response.data)
          })
          .catch(error => {
            console.log(error)
            reject(error)
          })
        })
    },
   

  }
})

export default Store;


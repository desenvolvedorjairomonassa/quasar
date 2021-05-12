import Vue from 'vue'
import Vuex from 'vuex'
import axios from 'axios'

Vue.use(Vuex)
//axios.defaults.baseURL = 'http://localhost:3000/api'

import example from './storemob';

export function acessoToken  (context, credentials)  {
    return new Promise((resolve, reject) => {
 
      console.log('context')
          axios.post('http://localhost:3000/api/Users/login', {
          username: credentials.username,
          password: credentials.password
        })
          .then(response => {
            const token = response.data.access_token

            localStorage.setItem('access_token', token)
            context.commit('acessoToken', token)
            resolve(response)
            // console.log(response);
            // context.commit('addTodo', response.data)
          })
          .catch(error => {
            console.log(this.$http)
            console.log(error)
            reject(error)
          })
        })
    }
   export function destroyToken(context) {
      axios.defaults.headers.common['Authorization'] = 'Bearer ' + context.state.token

      if (context.getters.loggedIn) {
        return new Promise((resolve, reject) => {
          axios.post('http://localhost:3000/api/Users/logout')
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
    }   
export function register(context, data) {
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
} 




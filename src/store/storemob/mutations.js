import * as state from './state';

export  function acessoToken(state, token) {
  state.token = token
}
export function destroyToken(state) {
  sate.token = null
}

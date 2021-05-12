<template>
    <q-page padding>
        <q-table 
        
        style="float:right;width:300px; border:10px ridge #C2CCCA; padding:20px; display:block"
        grid
        :data="cobrancas"
        row-key="parcela"
        :columns="columns"
        >  
        </q-table>
        <q-input style="float:left;width:100px;border:2px"
          v-model="pedido.quantidadeparcelas" 
          type="number"
          @change.native="atualizacao" />
        
        <q-datetime 
        v-model="pedido.inicio" 
        type="date" />
        <q-input 
            v-model="pedido.valorparcela" 
            type="number" prefix="R$" 
            stack-label="parcelas"
            @change.native="atualizacao" />
       
        <q-select
        float-label="Periodicidade"
        v-model="pedido.tipo"
        :options="tipo"
        @change="atualizacao" 
        >
            
        </q-select>    
        


       

    </q-page>
</template>
<script>
import { date } from 'quasar'
export default {
  data() {
    return {
        erroDocumento : false,
        pedido :
        {
            quantidadeparcelas: 1,
            inicio : new Date,
            valorparcela : 0 ,
            tipo : ''

        },
        tipo : [
            {label : 'Mensal',
            value : 'Mensal'},

            {label: 'Bimestral',
            value: 'Bimestral'},
            {
             value :'Trimestral',       
             label : 'Trimestral',
            },
            {value : 'Semestral',
             label : 'Semestral'},

            {value : 'Anual',
            label : 'Anual'},
            {value : 'Única',
            label : 'Única'}
            ],

        cobrancas : [],
        columns :[
            {name : "parcela",
            label: "n parcela",
            field: "parcela",
            style : 'width:5px' 
            },
            {name : "vencimento",
            label : "vencimento",
            field : "vencimento"}
        ]
    }

  },
  methods:{
      atualizacao () {
          this.cobrancas = []
          var vencInicial = new Date(this.pedido.inicio);
          var venc = new Date(this.pedido.inicio);
          console.log(this.pedido.inicio);
          for (let index =0; index < this.pedido.quantidadeparcelas; index++) {
              venc = new Date(this.pedido.inicio);
              switch (this.pedido.tipo) {
                  case 'Mensal': 
                    venc.setMonth(this.pedido.inicio.getMonth() + index)                     
                    break; 
                  case 'Bimestral':  
                    venc.setMonth(this.pedido.inicio.getMonth() + index*2)                     
                    break;   
                  case 'Trimestral':
                    venc.setMonth(this.pedido.inicio.getMonth() + index*3)                     
                    break;                                   
                  case  'Semestral':
                    venc.setMonth(this.pedido.inicio.getMonth() + index*6)   
                    break;
                  case 'Anual':                     
                    venc.setFullYear(this.pedido.inicio.getFullYear() + index*1)   
                    break;
                  default:
                    venc.setMonth(this.pedido.inicio.getMonth() + index)      
                      break;
              }
              

              console.log(index)
              console.log(this.pedido.quantidadeparcelas)
              let formattedString = date.formatDate(venc, 'DD/MM/YYYY') 
              console.log(formattedString)
              this.cobrancas.push({parcela: index+1, vencimento:  formattedString})                               
             
          }
          console.log(this.cobrancas)
        
      }
  }  
}
</script>
<style>
aside { 
    display: block;
}
</style>


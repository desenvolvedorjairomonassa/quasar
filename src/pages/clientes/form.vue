<template>
<q-page padding>
<q-btn icon="list" @click.native="voltar">Lista
  <q-tooltip>voltar a lista</q-tooltip>
</q-btn>
<div style="clear:both;">&nbsp;</div>
<div style="float:left;"  >
  <q-field  error-label="código obrigatório">
    <q-input  
      :disable="disable" 
      :error="($v.cliente.codigo.$dirty || erroValidacao) && $v.cliente.codigo.$invalid"
      v-model="cliente.codigo"   
      placeholder="0000" />
  </q-field>
</div>

  
  <q-field  style="float:left;"
   icon="person">  
    <q-select :disable="disable" width ="10px"
      v-model="cliente.tppessoa"
      float-label="Tipo de pessoa"
      align="left"
     :options="selectOptions"
    />
   </q-field>
  
   <div style="clear:both;">&nbsp;</div>
   <div style="float:left;width:550px" >
  <q-field 
  error-label='pelo menos 3 caracteres'>
   <q-input 
    
    :error="($v.cliente.razao.$dirty || erroValidacao) && $v.cliente.razao.$invalidc"
    @focus="$v.cliente.razao.$touch()"
    :disable="disable" 
    v-model="cliente.razao"   
    float-label="nome"
    />
  </q-field>  
  </div>
 
 <q-field >
   <q-input :disable="disable" v-model="cliente.fantasia"   float-label="fantasia"/>
 </q-field>
<br><br>
<q-field :error-label="mensagemErroDoc" style="float:left">
  <q-input 
  :disable="disable" 
  :error ="erroDocumento"
  @keyup="val => buscarCNPJ(cliente.documento,val)"
  v-model="cliente.documento"  
  float-label="CNPJ"
  class="doc"/>
</q-field>
<q-field style="float:left">
  <q-input :disable="disable" v-model="cliente.inscrMunicipal" float-label="Inscrição municipal"/>
</q-field>

<q-field style="float:left">
  <q-input :disable="disable" v-model="cliente.inscrEstadual" float-label="Inscrição estadual"/>
</q-field>
<q-field > 
  <q-input :disable="disable" v-model="cliente.suframa" float-label="Suframa"/>
</q-field>

<q-field  style="float:left"  icon="phone"
  
>
  <q-input :disable="disable"            
           @keyup="cliente.fone  = mascaraTelefone(cliente.fone)"
           v-model="cliente.fone"
           type="text" 
           float-label="Telefone"  />
</q-field>
<q-field style="float:left">
  <q-input :disable="disable"             
            @keyup="cliente.fone2 = mascaraTelefone(cliente.fone2)"
            v-model="cliente.fone2" 
            type="text" float-label="Telefone 2" />

</q-field>
<q-field :disable="disable" style="float:left">
  <q-input :disable="disable" 
  v-model="cliente.celular" 
  @keyup="cliente.celular = mascaraTelefone(cliente.celular)"
  type="text" 
  float-label="Celular" />

</q-field>
<q-field icon="mail"
         error-label="email inválido">

<q-input 
    :error="($v.cliente.email.$dirty  || erroValidacao) && $v.cliente.email.$invalid && (cliente.email.length > 1)"   
    @focus="$v.cliente.email.$touch()"
    :disable="disable" 
    v-model="cliente.email" 
    type="text"
    float-label="E-mail" 
/>

</q-field  >

<div style="clear:both;">&nbsp;</div>
<q-tabs v-model="cliente.selectTab" animated glossy>
  <q-tab name="endereco" default label="Endereço principal "  icon="far fa-address-card" slot="title"/>

  <q-tab name="cobranca" label="Endereço de cobrança" icon="fas fa-hand-holding-usd" slot="title" />
  <q-tab name="entrega" label="Endereço de entrega" icon="fas fa-truck" slot="title" />

  <q-tab-pane name="endereco">
    <q-field error-label="CEP não encontrado" style="float:left; width:300px">
      <q-input 
      :error="erroEndereco"
      :disable="disable" 
      @keyup="buscarCEP(cliente.endereco)"
      v-model="cliente.endereco.CEP" 
      float-label="CEP"
      type="text"/>
    </q-field>
    <q-field style="float:left; width:300px">
      <q-input :disable="disable" v-model="cliente.endereco.logradouro" float-label="logradouro"/> 
    </q-field>
    <q-field style="float:left; width:200px">
      <q-input :disable="disable" v-model="cliente.endereco.num" float-label="nº"/>
    </q-field>  
    <q-field >
      <q-input :disable="disable" v-model="cliente.endereco.complemento" float-label="complemento"/>
    </q-field>  
    <div style="clear:both">&nbsp;</div>
    <q-field style="float:left;width:500px ">
      <q-input :disable="disable" v-model="cliente.endereco.bairro" float-label="bairro"/>
    </q-field>  
    <q-field style="float:left;width:500px ">
      <q-input :disable="disable" v-model="cliente.endereco.cidade" float-label="cidade"/>
    </q-field>
       <q-field style="float:left;">  
        <q-select width ="10px"
          v-model="cliente.endereco.estado"
          float-label="estado"
          align="left"
        :options="optionsEstado"
        />
      </q-field>
      <q-field >  
        <q-select 
          v-model="cliente.endereco.pais"
          float-label="pais"
          align="left"
          
        :options="optionsPais"
        />
      </q-field>
     
   
       <q-btn 
         :disable="disable" 
         label="limpar"
         icon="clear"   
         @click.native="limpar(cliente.endereco)" 
         class="limpar"/> 
         <div style="clear:both;">&nbsp;</div>
     </q-tab-pane>
  <q-tab-pane name="cobranca">
    <q-field error-label="CEP não incontrado" style="float:left; width:300px">
      <q-input 
      :disable="disable" 
      :error="erroEnderecoCobranca"
      @keyup="buscarCEP(cliente.cobranca)"
      v-model="cliente.cobranca.CEP" 
      float-label="CEP"/>
    </q-field>
    <q-field style="float:left; width:300px">
      <q-input   :disable="disable"  v-model="cliente.cobranca.logradouro" float-label="Logradouro"/>
    </q-field>
    <q-field style="float:left; width:200px">
      <q-input  :disable="disable"  v-model="cliente.cobranca.num" float-label="Nº"/>
    </q-field>  
    <q-field >
      <q-input  :disable="disable"  v-model="cliente.cobranca.complemento" float-label="complemento"/>
    </q-field>  
    <div style="clear:both">&nbsp;</div>
    <q-field style="float:left;width:500px ">
      <q-input :disable="disable"  v-model="cliente.cobranca.bairro" float-label="bairro"/>
    </q-field>  
    <q-field style="float:left;width:500px ">
      <q-input :disable="disable"  v-model="cliente.cobranca.cidade" float-label="cidade"/>
    </q-field>
       <q-field style="float:left;">  
        <q-select width ="10px"
          :disable="disable" 
          v-model="cliente.cobranca.estado"
          float-label="Estado"
          align="left"
        :options="optionsEstado"
        />
      </q-field>
      <q-field >  
        <q-select 
          :disable="disable" 
          v-model="cliente.cobranca.pais"
          float-label="pais"
          align="left"
          
        :options="optionsPais"
        />
      </q-field>      
      <q-btn 
         :disable="disable" 
         label="limpar"
         icon="clear"   
         @click.native="limpar(cliente.cobranca)" 
         class="limpar"/> 
         <div style="clear:both;">&nbsp;</div>      
  </q-tab-pane>
  <q-tab-pane name="entrega">
     <q-field  error-label="CEP não incontrado" style="float:left; width:300px">
      <q-input 
       :disable="disable" 
       :error="erroEnderecoEntrega"
       @keyup="buscarCEP(cliente.entrega)"      
       v-model="cliente.entrega.CEP" 
       float-label="CEP"/>
    </q-field>
    <q-field style="float:left; width:300px">
      <q-input  :disable="disable"  v-model="cliente.entrega.logradouro" float-label="Logradouro"/>
    </q-field>
    <q-field style="float:left; width:200px">
      <q-input  :disable="disable"  v-model="cliente.entrega.num" float-label="Nº"/>
    </q-field>  
    <q-field >
      <q-input  :disable="disable"  v-model="cliente.entrega.complemento" float-label="complemento"/>
    </q-field>  
    <div style="clear:both">&nbsp;</div>
    <q-field style="float:left;width:500px ">
      <q-input  :disable="disable"  v-model="cliente.entrega.bairro" float-label="bairro"/>
    </q-field>  
    <q-field style="float:left;width:500px ">
      <q-input  :disable="disable"  v-model="cliente.entrega.cidade" float-label="cidade"/>
    </q-field>
       <q-field style="float:left;">  
        <q-select width ="10px"
         :disable="disable" 
          v-model="cliente.entrega.estado"
          float-label="Estado"
          align="left"
        :options="optionsEstado"
        />
      </q-field>
        
      <q-btn 
         :disable="disable" 
         label="limpar"
         icon="clear"   
         @click.native="limpar(cliente.entrega)" 
         class="limpar"/> 
  </q-tab-pane>
</q-tabs>

 <q-btn :disable="disable" label="salvar"  icon="save" color="info" @click.native="submitClientes" class="salvar"/> 
 
 <q-btn :disable="disable" label="cancelar" icon="cancel"   @click.native="voltar" class="cancelar"/>  
 
</q-page>

</template>
<script>
import { required, minLength, between, email } from 'vuelidate/lib/validators'
import uteis,{ somNum, validarCPF, validarCNPJ, aplica_mascara_cpfcnpj, mascaraCEP, mascaraTel } from '../../uteis.js';

export default {
   
   data () {
    return {  
      erroDocumento : false,
      mensagemErroDoc: '',   
      erroValidacao: false,
      erroEndereco: false,
      erroEnderecoCobranca : false,
      erroEnderecoEntrega : false,      
      achouEndereco: false,
      achouEnderecoEntrega : false,
      achouEnderecoCobranca : false,
      achouCNPJ : false,
      idcliente: this.$route.params.id,
      disable : this.$route.params.disable,
      cliente : {
        codigo:'',
        tppessoa: '',
        razao:'',
        fantasia:'',
        documento:'',
        inscrMunicipal:'',
        inscrEstadual:'',
        dataCadastro: new Date,
        fone: '',
        fone2:'',
        celular:'',
        email:'',
        suframa:'',
        selectTab:'endereco',
        endereco: 
          { 
            CEP:'',
            logradouro :'',
            num : '',
            complemento :'',
            bairro: '',
            cidade : '',
            ibge :'',
            estado: '',
            pais: 'Brasil',
          }

        ,
        cobranca: 
          { 
            CEP:'',
            logradouro :'',
            num : '',
            complemento :'',
            bairro: '',
            cidade : '',
            ibge: '',
            estado: '',
            pais: '',
          },
        entrega: 
          { 
            CEP:'',
            logradouro :'',
            num : '',
            complemento :'',
            bairro: '',
            cidade : '',
            ibge: '',
            estado: '',
            pais: '',
          }

        ,
      },  
      selectOptions: [
        {
          label: 'Física',
          value: 'F'
        },
        {
          label: 'Jurídica',
          value: 'J'
        }        
        ],
    optionsEstado :[
      	{label: "Acre", value: "AC"},
        {label: "Alagoas", value: "AL"},
        {label: "Amapá", value: "AP"},
        {label: "Amazonas", value: "AM"},
        {label: "Bahia", value: "BA"},
        {label: "Ceará", value: "CE"},
        {label: "Distrito Federal", value: "DF"},
        {label: "Espírito Santo", value: "ES"},
        {label: "Goiás", value: "GO"},
        {label: "Maranhão", value: "MA"},
        {label: "Mato Grosso", value: "MT"},
        {label: "Mato Grosso do Sul", value: "MS"},
        {label: "Minas Gerais", value: "MG"},
        {label: "Pará", value: "PA"},
        {label: "Paraíba", value: "PB"},
        {label: "Paraná", value: "PR"},
        {label: "Pernambuco", value: "PE"},
        {label: "Piauí", value: "PI"},
        {label: "Rio de Janeiro", value: "RJ"},
        {label: "Rio Grande do Norte", value: "RN"},
        {label: "Rio Grande do Sul", value: "RS"},
        {label: "Rondônia", value: "RO"},
        {label: "Roraima", value: "RR"},
        {label: "Santa Catarina", value: "SC"},
        {label: "São Paulo", value: "SP"},
        {label: "Sergipe", value: "SE"},
        {label: "Tocantins", value: "TO"}
    ],
    optionsPais :[ {label:"Brasil",value:"Brasil"}]
    }
   },
   validations: {
     cliente: {
      codigo : {
        required  
      },
      tppessoa: {
        required
      },
      razao : 
      { 
        required,
        minLength:  minLength(3)
      } ,
    /* fantasia : {
        required : requiredIf(function(){  
                    return this.cliente.tppessoa == 'J'
                  } )
      },*/
      "email" : {
       email
        }

     }

   },
   mounted() {
    console.log(this.$route.params.id);
  
   },
   created()  {
    if (this.idcliente!=0)  {
       this.$http.get('http://localhost:3000/api/clientes/'+this.idcliente)
      .then(res => res.json())
      .then(cliente => 
       {
          this.cliente.codigo = cliente.codigo,
          this.cliente.tppessoa = cliente.tppessoa,
          this.cliente.razao = cliente.razao,
          this.cliente.fantasia = cliente.fantasia,
          this.cliente.documento = cliente.documento,
          this.cliente.inscrMunicipal = cliente.inscrMunicipal,
          this.cliente.inscrEstadual = cliente.inscrEstadual,
          this.cliente.dataCadastro = cliente.dataCadastro
          this.cliente.fone = cliente.fone,
          this.cliente.fone2 = cliente.fone2,
          this.cliente.celular = cliente.celular,
          this.cliente.email = cliente.email,
          this.cliente.suframa = cliente.suframa,
          this.cliente.endereco = cliente.endereco || {}
          this.cliente.cobranca = cliente.cobranca || {}
          this.cliente.entrega = cliente.entrega || {}
        }
      
      
      
      , err => console.log(err));
    }

    },
   methods: {
      limpar(endereco) {
        this.achouEndereco = false;        
        this.achouEnderecoEntrega = false;  
        this.achouEnderecoCobranca = false;
        this.erroEndereco = false;        
        this.erroEnderecoCobranca = false;  
        this.erroEnderecoEntrega = false;
        endereco.logradouro = '' 
        endereco.num = '';
        endereco.complemento = '';
        endereco.estado = '';
        endereco.bairro = '';
        endereco.pais = '';
        endereco.cidade = '';
        endereco.CEP = '';
      },
     teste () {alert(this.$route.params.id)},
     voltar() {
       this.$router.push({path : '/clientes'});       
     },
     buscarCNPJ(documento,event,callback) {
      
      ///aplica_mascara_cpfcnpj(documento,18,event.key)
      //console.log(documento)
      // var masc = this.cliente.documento
      //aplica_mascara_cpfcnpj(masc,18,event.key)
      
      var cnpjvalido = false
      if (this.achouCNPJ) { 
         return false
         }
       var cnpj = somNum(this.cliente.documento)  
       console.log(cnpj)
       if (cnpj.length < 11) {
         return false
       }
       if (cnpj.length == 11) {
         var cpfvalido = validarCPF(cnpj);
         this.achouCNPJ = cpfvalido
         if (this.achouCNPJ) {
            this.mensagemErroDoc = '';
            this.erroDocumento = false

         }
         else
         {
            this.mensagemErroDoc = 'CPF incorreto';
            this.erroDocumento = true;

         }

         
         return cpfvalido;

       }
       else if (cnpj.length == 14) {
         
         var cnpjvalido = validarCNPJ(cnpj);
         console.log(cnpjvalido)
         this.achouCNPJ = cnpjvalido;
         if (this.achouCNPJ) {
            this.mensagemErroDoc = '';
            this.erroDocumento = false

         }
         else
         {
            this.mensagemErroDoc = 'CNPJ incorreto';
            this.erroDocumento = true;

         }

       }
       if (cnpjvalido) {
       var servidor = "https://www.receitaws.com.br/v1/cnpj/"+cnpj;
        //this.$httpProvider.defaults.headers.common['Access-Control-Allow-Origin'] = '*';
       // this.$http.defaults.headers.common['Access-Control-Allow-Origin'] = '*'
        // = 'http://www.novisistemas.com.br';
       this.$http({
             method: 'JSONP',
              url: servidor})
       .then (function(response){
         console.log(response.data)
         this.achouCNPJ = true
         this.cliente.endereco.bairro = response.data.bairro;
         this.cliente.endereco.logradouro = response.data.logradouro;
         if (response.data.telefone) {
            
           if (response.data.telefone.indexOf("/")>0) {
             var tel = response.data.telefone.split("/");
             this.cliente.fone = tel[0]
             this.cliente.fone2 = tel[1]
           }
           else {
            this.cliente.fone = response.data.telefone;
           }
         }
         this.cliente.endereco.num = response.data.numero;
         this.cliente.endereco.complemento = response.data.complemento;
         this.cliente.endereco.estado = response.data.uf
         if (response.data.cep) {
           var cep = response.data.cep.replace('.','');
            this.cliente.endereco.CEP = cep;
         }
        this.cliente.endereco.cidade = response.data.municipio;
        this.cliente.fantasia = response.data.fantasia;
        this.cliente.razao = response.data.nome;
        this.cliente.email = response.data.email;
        this.cliente.tppessoa = 'J'
        this.cliente.documento = response.data.cnpj;
       }).catch(error => {
            console.log(error)
            
          })
      }
     },
     
     buscarCEP(endereco,callback) {
       if (endereco.CEP.length < 5) {
         return false
       }
      endereco.CEP =  mascaraCEP(endereco.CEP)
     
      if (endereco.CEP.length < 8) {
         return false
       }   

       if (endereco.logradouro) {
         return false       
       }
       
       if (this.cliente.selectTab == 'endereco') {
         if (this.achouEndereco) 
        { return false} 
       }
       else if (this.cliente.selectTab == 'entrega') {
         if (this.achouEnderecoEntrega) 
          {return false}
       }
       else if (this.cliente.selectTab== 'cobranca') {
         if (this.achouEnderecoCobranca)  {
           return false
         }

       }  
      
       if(/^[0-9]{5}-[0-9]{3}$/.test(endereco.CEP) ||
          /^[0-9]{8}$/.test(endereco.CEP)
       
       ){
          var servidor = 'https://viacep.com.br/ws/'+ endereco.CEP + '/json/' ;
          
           this.$http.get( servidor,
          callback).then(function (response) {
            
            if (this.cliente.selectTab == 'endereco') {
             
             if (response.data.erro)   {
               this.erroEndereco = true
             } 
             else {
               this.erroEndereco = false
               this.achouEndereco = true;
             }
             
             
            }
            else if (this.cliente.selectTab == 'entrega') {
              
             if (response.data.erro)   {
               this.erroEnderecoEntrega = true
             }
             else {
               this.erroEnderecoEntrega = false
               this.achouEnderecoEntrega = true
             }
            }
            else if (this.cliente.selectTab == 'cobranca') {
             
              if (response.data.erro)   {
                this.erroEnderecoCobranca = true
             }
             else {
                 this.erroEnderecoCobranca = false
                  this.achouEnderecoCobranca = true;
             }


              }
            //endereco.CEP = response.data.cep
            endereco.logradouro = response.data.logradouro 
            endereco.bairro = response.data.bairro
            endereco.cidade = response.data.localidade
            endereco.estado = response.data.uf;              
            
          }).catch(error=>{
            console.log(error)
            
          })
          
       }
         // callback(JSON.stringify(data))
          

          

      }
     ,
     mascaraTelefone(telefone,callback) {
       if (!telefone) {
         return ''
       }
        
      
        return mascaraTel(telefone)
        
     },
     submitClientes () {
       console.log(this.$v.cliente.$invalid)
       this.erroValidacao = this.$v.cliente.$invalid
       if (this.$v.cliente.$invalid) {
         alert('Erros em vermelho')
         this.erroValidacao = true;
         return false
       }
    
       if (this.idcliente==0) {
         console.log(this.cliente);
         this.cliente.dataCadastro = new Date;
        this.$http.post('http://localhost:3000/api/clientes',
        {
              codigo: this.cliente.codigo,
          tppessoa: this.cliente.tppessoa,
          razao: this.cliente.razao,
          fantasia: this.cliente.fantasia,
          documento: this.cliente.documento,
          inscrMunicipal: this.cliente.inscrMunicipal,
          inscrEstadual: this.cliente.inscrEstadual,
          dataCadastro: new Date ,
          fone: this.cliente.fone,
          fone2: this.cliente.fone2,
          celular: this.cliente.celular,
          email: this.cliente.email,
          suframa: this.cliente.suframa,
          endereco : 
          { 
            CEP: this.cliente.endereco.CEP,
            logradouro : this.cliente.endereco.logradouro,
            num :  this.cliente.endereco.num,
            complemento: this.cliente.endereco.complemento,
            bairro: this.cliente.endereco.bairro,
            cidade : this.cliente.endereco.cidade,
            estado: this.cliente.endereco.estado,
            pais: this.cliente.endereco.pais,
          }              
          ,
          cobranca : 
          { 
            CEP: this.cliente.cobranca.CEP,
            logradouro : this.cliente.cobranca.logradouro,
            num :  this.cliente.cobranca.num,
            complemento: this.cliente.cobranca.complemento,
            bairro: this.cliente.cobranca.bairro,
            cidade : this.cliente.cobranca.cidade,
            estado: this.cliente.cobranca.estado,
            pais: this.cliente.cobranca.pais,
          }              
          ,
          entrega : 
          { 
            CEP: this.cliente.entrega.CEP,
            logradouro : this.cliente.entrega.logradouro,
            num :  this.cliente.entrega.num,
            complemento: this.cliente.entrega.complemento,
            bairro: this.cliente.entrega.bairro,
            cidade : this.cliente.entrega.cidade,
            estado: this.cliente.entrega.estado,
            pais: this.cliente.entrega.pais,
          }     
                
                             
       } 
       ).then( function (response) { 
         //console.log(JSON.stringify(response.data))
         //clonar objeto    JSON.encode (JSON.stringify(this.$data))
         this.$router.push({path : '/clientes'});   
       }, function (response) {
                     console.log(JSON.stringify(response.data))
                     alert('sem comunicação')
                    }
       );   
           
       } else {
         // atualização
        this.$http.put('http://localhost:3000/api/clientes/'+this.idcliente, this.cliente)
        .then( function (response) { 
         //console.log(response.data)
         this.$router.push({path : '/clientes'});   
         }, function (response) {
                     console.log(response.data)
                     alert('sem comunicação')
                    }
       );   
       }
       
     }

   },

}

</script>

<style >




</style>

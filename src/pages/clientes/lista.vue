<template>
<q-page padding>
   <q-icon style="align:left" name="fas fa-search" />
  <q-input v-model="filtro" type="search" 
float-label="Pesquisar"  >

  </q-input>

  <q-table
      grid
      :filter="filtro"
      :filter-method="filtroCliente"
      :data="clientes"
      :config="configura"
      :pagination.sync="pagination"
      :loading="loading"
      :columns="columns"          
      row-key="codigo"
      :refresh="refresh"
    >
    <q-tr slot="top-row" slot-scope="props" >
        <q-td colspan="100%" color ="info">
          <q-btn flat to="/clientes/form/0" >
          <q-icon name="add_circle" />
          <strong> novo </strong>
        </q-btn>     
        </q-td>
    </q-tr>

  <q-td slot="body-cell-acoes" slot-scope="props" :props="props">
      <q-btn flat @click.native="editar(props.row)">
      <q-icon name="edit" />
      </q-btn>    
      <q-btn flat  @click.native="visualizar(props.row)"> 
      <q-icon name="far fa-eye"  />
      <q-tooltip>visualizar cliente, não permite editar</q-tooltip>
      </q-btn>
      <q-btn  flat  @click.native="remover(props.row)">
      <q-icon name="delete" color="red"/>
      <q-tooltip>excluir cliente</q-tooltip>
      </q-btn>    
  </q-td>


  </q-table>
</q-page>
</template>

<script>

export default {
  data() {
    return {
        filtro: '',
        loading: false,
        refresh: false,
        clientes : [],
        separator: 'horizontal',
        configura: {
          rowHeight: '50px',
          columnPicker: true,
         
          },
          pagination: {
            rowsPerPage: 15,
            page: 1,
            options: [30, 60, 90, 120, 150, 500]
          } ,         
        columns : [
         { 
          acoes :'acoes' ,
          name : 'acoes',
          label: 'Ações',
          align: 'left',
          sortable: false,
          classes: 'acoes',
          style: 'width: 10px',
         },     
        {
        documento: 'documento',
        required: true,
        label: 'CNPJ/CPF',
        align: 'left',
        field: 'documento',
        sortable: true,
        classes: 'cli_documento',
        style: 'width: 100px',
       
        },            
       
        {
        codigo: 'codigo',
        required: true,
        label: 'Código',
        align: 'left',
        field: 'codigo',
        sortable: true,
        classes: 'cli_codigo',
        style: 'width:80px'
        },
        {
        razao: 'razao',
        required: true,
        label: 'Nome',
        align: 'left',
        field: 'razao',
        sortable: true,
        classes: 'cli_razao',
        style: 'width: 500px'
        },
        {cidade: 'endereco.cidade',
        label :'Cidade',
        field: 'endereco.cidade',
        classes: 'cli_cidade'},        
    ]
    }
  },

  methods :{
    filtroCliente (rows, filtro, cols, cellValue) {
      const lowerTerms = filtro ? filtro.toLowerCase() : ''
      return rows.filter(
        row => cols.some(col => (cellValue(col, row) + '').toLowerCase().indexOf(lowerTerms) !== -1)
      )
    },
    remover(clientes) {
       if (confirm('Deseja excluir')) {
          this.refresh= true;
          this.$http.delete('http://localhost:3000/api/clientes/'+clientes.id)
        .then((res)=>{
          this.$router.go(this.$router.currentRoute);
          this.refresh = false ;
          console.log(res.data);

        }, err => console.log(err));
          
       }     

    },
    editar(clientes) {
      const idCli = clientes.id;
      this.$router.push({name: "clienteForm", params: {id: idCli, disable:false} });
        //{path:`/clientes/form/${clientes.id}`})
    },
    visualizar(clientes) {
      const idCli = clientes.id;
     
      this.$router.push({name: "clienteForm", params: {id: idCli, disable:true} })
    }
  },
  
  created() {

    this.$http.get('http://localhost:3000/api/clientes')
      .then(res => res.json())
      .then(clientes => this.clientes = clientes, err => console.log(err));
    }
}

</script>
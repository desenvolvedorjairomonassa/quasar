/******************************************************************************

age of cities

*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <stdbool.h>
int numeroJogadores;

struct mapa {
	int madeira;
    int pedra;
    int alimento;
    int ocupadoJogador; // mapa ocupado por 
	
};
struct recursos_jogadores
  {
    int casas;
    int construindoCasa; //turnos falta terminar
    int construindoQuartel; //turnos falat terminar
    int construindoMuralha; 
    int construindoTemplo;
    int habitantes;
	int posicaoxIni; //posicao inicial até 20
	int posicaoyIni; //posicao inicial até 25
    int madeira;
    int pedra;
    int alimento ; 
	int cidades; //a cada 10 posicoes
    int turnos;
    int templo;
    int muralha;
    int quartel;
	int posicaoConquistada;//quantidade posicao consquistada no mapa
    int soldadoCidade; //quantidade
    int soldadoGuerra;


    int foraJogo;		//1 - ainda jogando ; 0 fora do jogo

  };

  // baixa os recursos se houver disponibilidade
  //baixo tudo solicitado ou somente o que tem na area
int baixarRecursosMadeira(struct mapa *mapa,int saldoBaixar)//passando por referencia
{
  int saldoRestante;	 
  if ((*mapa).madeira >= saldoBaixar )
  {
	(*mapa).madeira = (*mapa).madeira - saldoBaixar;  
    return 0;
  }
  else 
  {
	saldoRestante = (*mapa).madeira;    
	(*mapa).madeira = 0; // coletou tudo que o mapa ainda tinha
    return saldoRestante;
  }
	
}  
int baixarRecursosPedra(struct mapa *mapa,int saldoBaixar)
{
  int saldoRestante;	 
  if ((*mapa).pedra >= saldoBaixar )
  {
	(*mapa).pedra = (*mapa).pedra - saldoBaixar;  
    return 0;
  }
  else 
  {
	saldoRestante = (*mapa).pedra;    
	(*mapa).pedra = 0; // coletou tudo que o mapa ainda tinha
    return saldoRestante; // mas ainda faltou
  }
	
}  
void preencherMapa( struct mapa *mapa)
{
	(*mapa).madeira = 400 + (rand () % 1600); //randomizando de 400 a 2000
	(*mapa).pedra = 400 + (rand () % 1600);
	(*mapa).alimento = rand() %100;
	(*mapa).ocupadoJogador = -1;
	
}
void mostrarRecursos (struct recursos_jogadores recursos)
{
  printf("\n tem %i casas e contruindo %i \t ",recursos.casas,  recursos.construindoCasa);
  if (recursos.construindoQuartel>0) {
   printf(" contruindo quartel faltando %i turnos. ",recursos.construindoQuartel);
  }
  if ( recursos.quartel == 1) {
	printf("possui quartel. ");}
  if (recursos.construindoTemplo>0 ) {
	printf("construindo um templo faltando %i turnos. ",recursos.construindoTemplo);}
  if (recursos.construindoMuralha>0){
  printf(" construindo muralha faltando %i turnos para terminar. ",recursos.construindoMuralha);}
  if (recursos.muralha == 1) {
  printf(" possui muralha.");}
  if (recursos.templo == 1){
  printf(" possui templo. ");}
  if (recursos.madeira>0) {
   printf(" em estoque %i em madeiras. ",recursos.madeira);}
  if (recursos.pedra>0) {
  printf(" em posse %i pedras. ",recursos.pedra);}
  if (recursos.alimento>0){
   printf(" possui %i alimentos em estoque. ",recursos.alimento);}
  printf("possui %i habitantes. ",recursos.habitantes);
  if (recursos.soldadoCidade >0)
  {printf(" Tem %i soldados na cidade e %i na guerra.", recursos.soldadoCidade,recursos.soldadoGuerra); }
}
void inicializandoRecursos(struct recursos_jogadores *recursos)
{
    (*recursos).foraJogo = 1;
    (*recursos).habitantes = 10 ;
    (*recursos).posicaoxIni =   (rand () % 20); //0 até 20
	(*recursos).posicaoyIni =   (rand () % 25); //0 até 25

     (*recursos).madeira = 0;
     (*recursos).pedra = 0;
     (*recursos).alimento = 0;
	 (*recursos).cidades = 0;
     (*recursos).casas = 0;
     (*recursos).quartel = 0 ;
     (*recursos).muralha = 0;
      (*recursos).templo =0;
     (*recursos).construindoQuartel = 0;
     (*recursos).construindoCasa =0;
     (*recursos).construindoMuralha = 0;
     (*recursos).construindoTemplo = 0;
     (*recursos).soldadoCidade = 0;
     (*recursos).soldadoGuerra = 0;
}

 //passando os turnos e verificando se contruio algo 
void contruindo(struct recursos_jogadores *recursos)
{  //se tiver contruindo casa
   if ((*recursos).construindoCasa >0)
   {
     --(*recursos).construindoCasa;
     //casa pronta -- minha casa minha vida para 10 hab
     if ((*recursos).construindoCasa == 0)
     {
       ++(*recursos).casas;   
       printf("Parabens 1 casa terminada\n");
       if ((*recursos).casas == 1 )
       {
       	(*recursos).cidades = 1; // inicio da cidade e 1 casa
	   }
       (*recursos).habitantes=(*recursos).habitantes+10;       
       
     }
   }
   
  if ((*recursos).construindoQuartel >0) 
  {
     --(*recursos).construindoQuartel;
     //quartel pronto ?
     if ((*recursos).construindoQuartel ==0)
     {
       ++(*recursos).quartel;
     } 
  }
  if ((*recursos).construindoMuralha >0) 
  {
     --(*recursos).construindoMuralha;
     //quartel pronto ?
     if ((*recursos).construindoMuralha ==0)
     {
       ++(*recursos).muralha;
     } 
  }

   if ((*recursos).construindoTemplo >0) 
  {
     --(*recursos).construindoTemplo;
     //quartel pronto ?
     if ((*recursos).construindoTemplo ==0)
     {
       ++(*recursos).templo;
     } 
  }
}
void construirCasa (struct recursos_jogadores * recursos)
{
	(*recursos).madeira = (*recursos).madeira -25;
	(*recursos).pedra  = (*recursos).pedra -25;
	(*recursos).construindoCasa = 5; //turno para construir
}
bool podeConstruirCasa (struct recursos_jogadores recursos)  
{  // 25 madeira, 25 pedra e 5 turnos
 //tem recurso suficiente
  return (recursos.madeira >=25 && recursos.pedra >= 25 && recursos.habitantes>=5);
  
}
void construirQuartel(struct recursos_jogadores * recursos)
{
 (*recursos).madeira = (*recursos).madeira -60;	
 (*recursos).pedra = (*recursos).pedra -50;
 (*recursos).construindoQuartel = 15;
}
bool podeConstruirQuartel(struct recursos_jogadores recursos)
{//60 madeira 15 turnos 50 pedras

 return (recursos.madeira>=60 && recursos.pedra>=50 && recursos.habitantes>=5);

}
void contruirMuralha(struct recursos_jogadores * recursos)
{
 (*recursos).madeira = (*recursos).madeira -120;	
 (*recursos).pedra = (*recursos).pedra -120;
 (*recursos).construindoMuralha = 35;	
}
bool podeConstruirMuralha(struct recursos_jogadores recursos)
{//120 madeira 120 pedras 35 turnos
  return (recursos.madeira >= 120 && recursos.pedra >=120  && recursos.habitantes>=5);

}
void construirTemplo(struct recursos_jogadores * recursos)
{
  (*recursos).madeira = (*recursos).madeira -50;	
  (*recursos).pedra = (*recursos).pedra -50;
  (*recursos).construindoTemplo = 15 ;	
}
bool podeConstruirTemplo(struct recursos_jogadores recursos)
{//50 madeiras e pedras e  15 turnos
  return (recursos.madeira>=50 && recursos.pedra >= 50  && recursos.habitantes>=5);
}
int calculoTempoGasto (clock_t inicio)
{
  clock_t atual;
  atual = clock ();
  double segundos;
  segundos = (double) (atual - inicio) / (double) CLOCKS_PER_SEC;
  return segundos / 60;
}

int
main (void)
{
  int jogadoresRestantes;
  int tempoJogo, tempoGasto;
  int jogador, jogadorTurno;			// jogador atual
  int posicaox, posicaoy;
  clock_t tempoInicial, tempoAtual;
  tempoInicial = clock ();
  int extrair ; 
  srand((unsigned)time(NULL));
 
  do
    { 
      printf ("Digite numero jogadores:\t");
      scanf ("%i", &numeroJogadores);
      if (numeroJogadores <= 1)
	{  system("cls"); 
	  printf ("Deve jogar mais de um jogador.\n");

	}
    }
  while (numeroJogadores <= 1);

  
  printf ("Digite o tempo em minutos de jogo:\t");
  scanf ("%i", &tempoJogo);
  printf ("%i jogadores\n", numeroJogadores);

  struct recursos_jogadores recursos[numeroJogadores-1];
  struct mapa mapa [20] [25]; // criação do matrix do mapa
  //prencher o mapa com recursos
  for(posicaox=0;posicaox<20;++posicaox)
  {
	  for(posicaoy=0;posicaoy<25;++posicaoy)
	  {  // preenche as posicoes do mapa com recursos aleatorios
		  preencherMapa(&mapa[posicaox][posicaoy]);
	  }	  
  }	
  
  jogadoresRestantes = numeroJogadores;
  //iniciando as variaveis
  for(jogador=0;jogador<numeroJogadores;++jogador)
  { inicializandoRecursos(&recursos[jogador]);
    mapa [recursos[jogador].posicaoxIni] [recursos[jogador].posicaoyIni].ocupadoJogador = jogador;
  }
  while ((jogadoresRestantes > 1) || (tempoJogo > tempoGasto))
    {
      //loop da vez dos jogadores 
      // jogador = jogador da vez
      for (jogador = 0; jogador < numeroJogadores; ++jogador)
	    { 
        if (recursos[jogador].foraJogo == 0 ) {continue;} // jogador fora -passa a vez para proximo jogador
        printf ("Jogador %i: \t",jogador+1);
		mostrarRecursos(recursos[jogador]);
		
		  int opcao;
		  do{
		   
			
			printf ("\n Digite a opcao de jogo:\n",jogador+1);
			printf ("1 - Coletar\n");
			printf ("2 - Construir\n");
			printf ("3 - Convocar habitante para soldados");
			printf ("4 - Defender\n");
			printf ("5 - Atacar\t");
			scanf ("%i", &opcao);
			system("cls"); }
			while (opcao <1 || opcao >5);
		  switch (opcao)
		  {
			case 1: //coletar 
			  do{
			  system("cls"); 
			  printf ("Jogador %i . O que Coletar :\n",jogador+1);
			  printf ("1 - Madeira\n");
			  printf ("2 - Pedra\n");
			  printf ("3 - Alimento\t");
			  scanf ("%i", &opcao);}
			  while (opcao <1 || opcao >3);

			  switch (opcao) 
			  {  //recursos 1 para 10 habitantes
				case 1:
				 extrair = (10*recursos[jogador].habitantes); // quanto vai coletar 1/10 habitantes
				 	
					 for(posicaox=0;posicaox<20 && extrair > 0;++posicaox)
					  {   
						  for(posicaoy=0;posicaoy<25 && extrair > 0;++posicaoy)
						  { printf("posicao %i,%i mapa ocupador por  %i\n",posicaox,posicaoy,mapa[posicaox][posicaoy].ocupadoJogador);
							  if ( mapa[posicaox][posicaoy].ocupadoJogador == jogador) //COLETAR SOMENTE recursos/POSICAO EM SUA POSSE
								{
									extrair = baixarRecursosMadeira(&mapa[posicaox][posicaoy],extrair);
								}
						  }	  
					  }	
					 //vai receber tudo que puder extrair de suas terras desconsiderando o que não conseguiu	  
					 recursos[jogador].madeira=recursos[jogador].madeira+ (10*recursos[jogador].habitantes)- extrair;
					break;

				case 2: //baixarRecursosPedra
					extrair = (10*recursos[jogador].habitantes); // quanto vai coletar 1/10 habitantes
					 for(posicaox=0;posicaox<=20 && extrair > 0;++posicaox)
					  {
						  for(posicaoy=0;posicaoy<=25 && extrair > 0;++posicaoy)
						  { 
							  if ( mapa[posicaox][posicaoy].ocupadoJogador == jogador) //COLETAR SOMENTE recursos/POSICAO EM SUA POSSE
								{
									extrair = baixarRecursosPedra(&mapa[posicaox][posicaoy],extrair);
								}
						  }	  
					  }				
					 recursos[jogador].pedra = recursos[jogador].pedra +(10*recursos[jogador].habitantes)-extrair;
				break;

				case 3: //recursos ilimitados
					recursos[jogador].alimento = recursos[jogador].alimento+ (10*recursos[jogador].habitantes);
					break;
				

			  }
			break;
			// contruir o que 
			case 2:
			   do{
			  system("cls"); 
			  printf ("Jogador %i . O que construir :\n",jogador+1);
			  printf ("1 - Casa\n");
			  printf ("2 - Quartel\n");
			  printf ("3 - Muralha\n");
			  printf( "4 - Templo\n");
			  scanf ("%i", &opcao);}
			  while (opcao <1 || opcao >4);
			  switch (opcao) 
			  {
				case 1:
				 if (podeConstruirCasa(recursos[jogador]))
				 {
				   construirCasa(&recursos[jogador]);
				   
				 }
				 else
				 {printf("Nao pode contruir casa\n");
				 } 
				break;

				case 2:
				if (recursos[jogador].quartel==1)
				{ 
				  printf("Já possui quartel");
				}
				else
				if (podeConstruirQuartel(recursos[jogador]))
				{ construirQuartel(&recursos[jogador]);}
				else
				{printf("Nao pode contruir quartel\n");}
				break;

				case 3:
				  if (podeConstruirMuralha(recursos[jogador]))
				  {
					construirTemplo(&recursos[jogador]);
				  }
				  else
				{printf("Nao pode contruir muralha\n");}
				break;

				case 4:
				  //verifica se tem recursos disponivel para construir o templo
				  if (podeConstruirTemplo(recursos[jogador]))
				  {
					construirTemplo(&recursos[jogador]);
				  }
				break;
			  }


			break;
			case 3: 
			    //  para ter soldado precisa ter o quartel construido
			    if (recursos[jogador].quartel == 1 )  
			    {
			    	++recursos[jogador].soldadoCidade ;
				}
				else
				{
				  printf("sem quartel não pode ter soldado")	 ;
				}
			  break;
			case 4: 
			break;
		  }
		   
 			//processar no final de cada turno e verifica se terminou de construir algo de algum jogador
        for(jogadorTurno=0;jogadorTurno<numeroJogadores;++jogadorTurno)
        { //se tiver fora do jogo , nem checa 
          if (recursos[jogadorTurno].foraJogo == 0 ) {continue;} 
           contruindo(&recursos[jogadorTurno] );//verifica se tem tem algo construindo
		  //verifica se tem alimento no estoque de cada jogador, se não houver diminui um habitante
          // caso tenha nasce mais um		  
          if (recursos[jogadorTurno].alimento == 0 )
		   {
		    --recursos[jogadorTurno].habitantes;
		  } 
		  else
		  {
		  	 ++recursos[jogadorTurno].habitantes;
		  }
		   //perdeu habitante e ficou sem, sai do jogo
           if (recursos[jogadorTurno].habitantes == 0 ){
           	recursos[jogadorTurno].foraJogo = 0 ; //fora de jogo
		   }
         }
       
       
	    }	//fim-for

    }	//fim-while  


    // saiu do jogo teve um ganhador
	for(jogador=0;jogador<numeroJogadores;++jogador)
    {
		if (recursos[jogador].foraJogo == 1 ) // o unico que ficou dentro do jogo
		{
			printf("vencedor jogador %i ",jogador+1);
			break;
		}	
	}

   return 0;
}
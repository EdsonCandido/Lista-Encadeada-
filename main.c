/*
* autor: Edson Cândido
* Listas Duplamente Encadeadas - C
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(a) (a *) malloc ( sizeof(a) )

struct no{
   int info;
   struct no *prox;
   struct no *ant;
};

struct no *inicio;
struct no *fim;

void inserir ( int info ){
   struct no *novo = MALLOC ( struct no );
   struct no *atual;
        
   if ( !novo ){
      perror ( "Malloc: " );
      return ;
   }

   novo->info = info;
    
   if ( !inicio ){
      novo->prox = NULL;
      novo->ant  = NULL;
                
      inicio = novo;
      fim = novo;
                
      return ;
   }
    
   atual = inicio;
        
   while ( atual ){
      if ( atual->info < info )
         atual = atual->prox;
      else{
         if ( atual->ant ){
            novo->prox = atual;
            novo->ant = atual->ant;
            atual->ant->prox = novo;
            atual->ant = novo;
                                
            return ;
         }
         novo->prox = atual;
         novo->ant = NULL;
         atual->ant = novo;
         inicio = novo;
                        
         return ;
      }
   }
   fim->prox = novo;
   novo->prox = NULL;
   novo->ant = fim;
   fim = novo;
   
   return ;
}

void imprimeLista ( void ){
   struct no *atual = inicio;
        
   while ( atual ){
      printf ( "Info:  %.2d\n", atual->info );
      atual = atual->prox;
   }
   return ;
}

struct no *procurar ( int info ){
   struct no *atual = inicio;
        
   while ( atual ){
      if ( atual->info == info) 
         return atual;
      else
         atual = atual->prox;
   }
   return NULL;
}

void remover ( struct no *dado ){  
   if ( !dado ) return ;
        
   if ( dado->prox && dado->ant ){
      dado->ant->prox = dado->prox;
      dado->prox->ant = dado->ant;
                
      free ( dado );
      return ;
   }
        
   if ( dado == inicio ){
      inicio = dado->prox;
      inicio->ant = NULL;
                
      free ( dado );
      return ;
   }
        
   if ( dado == fim ){
      fim = dado->ant;
      fim->prox = NULL;
                
      free ( dado );
      return ;
   }
}

void main (){
   register int i;
   inicio = fim = NULL;
        
   for ( i = 1; i <= 10; i++ )
      inserir (i);
        
   imprimeLista(); puts ("");
        
   inserir (0);  
   inserir (12); 
   inserir (11);
        
   imprimeLista ();
   printf("\n");
   printf ("Procurar( 3 ): %.2d\n\n", procurar(3)->info );

   remover ( procurar ( 0) );
   remover ( procurar ( 5) );
   remover ( procurar (12) );
        
   imprimeLista(); puts ("");
}
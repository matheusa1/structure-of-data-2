#include "abb.h"


int main() {
    printf("Primeira árvore:\n\n");
    ABB* abb1 = NULL;

    ABB_Inserir(&abb1, 70);
    ABB_Inserir(&abb1, 39);
    ABB_Inserir(&abb1, 88);

    // ABB_Remover(&abb1, 70);
    
    ABB_Imprimir(abb1, 0, 'r');
    printf("\n==============================================================\n");

    printf("Segunda árvore:\n\n");  
    ABB* abb2 = NULL;

    ABB_Inserir(&abb2, 10);
    ABB_Inserir(&abb2, 4);
    ABB_Inserir(&abb2, 20);
    ABB_Inserir(&abb2, 6);
    ABB_Inserir(&abb2, 2);
    ABB_Inserir(&abb2, 3);
    ABB_Inserir(&abb2, 5);
    ABB_Inserir(&abb2, 7);

    // ABB_Remover(&abb2, 10);
    // ABB_Remover(&abb2, 4);
    // ABB_Remover(&abb2, 5);
      
    ABB_Imprimir(abb2, 0, 'r');

    printf("\n==============================================================\n\n");
    // 0, 30, 15, 20
    printf("Terceira árvore:\n\n");
    ABB* abb3 = NULL;
    
    ABB_Inserir(&abb3, 30);
    ABB_Inserir(&abb3, 50);
    ABB_Inserir(&abb3, 40);
    ABB_Inserir(&abb3, 47);
    ABB_Inserir(&abb3, 15);
    ABB_Inserir(&abb3, 20);
    ABB_Inserir(&abb3, 25);
    ABB_Inserir(&abb3, 17);
    ABB_Inserir(&abb3, 19);
    ABB_Inserir(&abb3, 4);
    ABB_Inserir(&abb3, 7);
    ABB_Inserir(&abb3, 0);

    ABB_Imprimir(abb3, 0, 'r');

    // ABB_Remover(&abb3, 0);
    // ABB_Remover(&abb3, 30);
    // ABB_Remover(&abb3, 15);
    // ABB_Remover(&abb3, 20);

    return 0;
}
#include "abb.h"
#include <stdlib.h>

// ----------------------------------------------------------------
//                      FUNÇÃO AUXILIAR
// ----------------------------------------------------------------

void Imprimir_No(int chave, int cont, char tipo) {
    for (int i = 0; i < cont; i++) printf("    ");
    printf("(%c) %d\n", tipo, chave);
}

ABB** Busca_no(ABB** temp) {
    if((*temp)->esq == 0) return temp;
    Busca_no(&(*temp)->esq);
}

void Remove_No(ABB** A) {
    if((*A)->dir == NULL && (*A)->esq == NULL) {
        (*A) = NULL;
    }

    if((*A)->dir == NULL && (*A)->esq != NULL) {
        (*A) = (*A)->esq;
    }

    if((*A)->esq == NULL && (*A)->dir != NULL) {
        (*A) = (*A)->dir;
    }

    if((*A)->esq != NULL && (*A)->dir != NULL) {
        ABB** temp = Busca_no(&(*A)->dir);
        
        (*A)->chave = (*temp)->chave;
        Remove_No(temp);
    }
}

// ----------------------------------------------------------------
//                  IMPLEMENTAÇÃO DA INTERFACE
// ----------------------------------------------------------------


ABB* ABB_Buscar(ABB* A, int chave) {
    if(A == NULL) return NULL;
    if(A->chave == chave) return A;
    
    if(chave < A->chave) return ABB_Buscar(A->esq, chave);
    else return ABB_Buscar(A->dir, chave);
}

ABB* ABB_Criar(int chave, ABB* esq, ABB* dir) {
    ABB* novo = (ABB*) malloc (sizeof(ABB));

    novo->chave = chave;
    novo->dir = dir;
    novo->esq = esq;

    return novo;
}

void ABB_Inserir(ABB** A, int chave) {
    if((*A) == NULL) {
        (*A) = ABB_Criar(chave, NULL, NULL);
        return;
    } else if(chave < (*A)->chave) {
        ABB_Inserir(&(*A)->esq, chave);
    } else ABB_Inserir(&(*A)->dir, chave);
}

void ABB_Imprimir(ABB* A, int cont, char tipo) {
    if (A == NULL) {
        return;
    }
    ABB_Imprimir(A->dir, cont+1, 'd');
    Imprimir_No(A->chave, cont, tipo);
    ABB_Imprimir(A->esq, cont+1, 'e');
}

void ABB_Remover(ABB** A, int chave) {
    if((*A)->chave == chave) {
        Remove_No(A);
    } else if(chave < (*A)->chave) ABB_Remover(&(*A)->esq, chave);
    else ABB_Remover(&(*A)->dir, chave);
}
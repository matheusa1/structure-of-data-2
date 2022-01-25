#include "ABB.h"
#include <stdlib.h>
#include <stdio.h>

// ----------------------------------------------------------------
//                      FUNÇÃO AUXILIAR
// ----------------------------------------------------------------

void ABB_Altura(ABB* A, int* maxSize, int size) {
    if(A == NULL) {
        if(*maxSize < size - 1) *maxSize = size - 1;
        return;
    }
    ABB_Altura(A->esq, maxSize, size + 1);
    ABB_Altura(A->dir, maxSize, size + 1);
}

unsigned int random_32bits() {
    unsigned int x;
   
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;

    return x;
}

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
        return;
    }

    if((*A)->dir == NULL && (*A)->esq != NULL) {
        (*A) = (*A)->esq;
        return;
    }
    if((*A)->esq == NULL && (*A)->dir != NULL) {
        (*A) = (*A)->dir;
        return;
    }

    if((*A)->esq != NULL && (*A)->dir != NULL) {
        ABB** temp = Busca_no(&(*A)->dir);
        
        (*A)->chave = (*temp)->chave;
        Remove_No(temp);
    }
}

void ABB_Sort_R(int* v, ABB* A, int* index) {
    if(A == NULL) return;
    
    ABB_Sort_R(v, A->esq, index);
    v[*index] = A->chave;
    *index = *index + 1;
    ABB_Sort_R(v, A->dir, index);
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

float ABB_Sort(int* v, int n) {
    ABB* A = NULL;

    for(int i = 0; i < n; i++) {
        ABB_Inserir(&A, v[i]);
    }

    int maxSize = 0;
    ABB_Altura(A, &maxSize, 0);

    int index = 0;

    ABB_Sort_R(v, A, &index);

    return (float) maxSize;
}

int* random_vector(int n, int max, int seed) {
    int* vector = (int*) calloc(n, sizeof(int));

    srand(seed);
    for(int i = 0; i < n; i++) {
        vector[i] = random_32bits() % max;
    }
    return vector;
}
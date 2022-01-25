#include "ARN.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// ----------------------------------------------//
//              FUNÇÕES AUXILIARES               //
// ----------------------------------------------//

void arnSize(Arn* A, int* maxSize, int size) {
    if(A == NULL) {
        if(*maxSize < size - 1) *maxSize = size - 1;
        return;
    }
    arnSize(A->left, maxSize, size + 1);
    arnSize(A->right, maxSize, size + 1);
}

unsigned int random_32bits() {
    unsigned int x;
   
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;

    return x;
}

Arn* arnCreate(TypeData data){
    Arn* new = (Arn*) malloc(sizeof(Arn));

    new->data = data;
    new->left = NULL;
    new->right = NULL;
    new->color = C_RED;

    return new;
}

static bool inline isRed(Arn* A){
    if(A == NULL) return false;
    return A->color == C_RED ? true : false;
}

static void changeColor(Arn* A) {
    A->color = C_RED;
    A->left->color = C_BLACK;
    A->right->color = C_BLACK;
}

static void rotLeft(Arn** A) {
    Arn* h;
    Arn* x;

    h = *A;
    x = h->right;

    h->right = x->left;
    x->left = h;

    x->color = h->color;
    h->color = C_RED;

    *A = x;
}

static void rotRight(Arn** A) {
    Arn* h;
    Arn* x;
// ATRIBUI VALORES A H E X
    h = *A;
    x = h->left;
// AJUSTA OS PONTEIROS
    h->left = x->right;
    x->right = h;
// AJUSTA AS CORES
    x->color = h->color;
    h->color = C_RED;

    *A = x;
}

void arnInsert_R(Arn** A, TypeData data) {
    if((*A) == NULL) {
        *A = arnCreate(data);
        return;
    }

    if(data.id <= (*A)->data.id) {
        arnInsert_R(&(*A)->left, data);
    }

    if(data.id > (*A)->data.id) {
        arnInsert_R(&(*A)->right, data);
    }

    if(isRed((*A)->right) && !isRed((*A)->left)) {
        rotLeft(A);
    }

    if(isRed((*A)->left) && isRed((*A)->left->left)) {
        rotRight(A);
    }

    if(isRed((*A)->right) && isRed((*A)->left)) {
        changeColor(*A);
    }
}

void printNode(TypeData data, int size, char position) {
    for (int i = 0; i < size; i++) printf("    ");
    printf("(%c) %d\n", position, data);
}

void ARN_Sort_R(TypeData* vetor, Arn* A, int* index) {
    if(A == NULL) return;
    
    ARN_Sort_R(vetor, A->left, index);
    vetor[*index] = A->data;
    *index += 1;
    ARN_Sort_R(vetor, A->right, index);
}

// ----------------------------------------------//
//                IMPLEMENTAÇÕES                 //
// ----------------------------------------------//

void arnInsert(Arn** A, TypeData data) {
    arnInsert_R(A, data);
    (*A)->color = C_BLACK;
}

void arnPrint(Arn* A, int size, char position) {
    if(A == NULL) {
        return;
    }
    arnPrint(A->right, size+1, 'd');
    printNode(A->data, size, position);
    arnPrint(A->left, size+1, 'e');
}

void ARN_Sort(TypeData* v, int n){
    Arn* A = NULL;

    for(int i = 0; i < n; i++) {
        arnInsert(&A, v[i]);
    }
    
    int index = 0;
    ARN_Sort_R(v, A, &index);
}

int* random_vector(int n, int max, int seed) {
    int* vector = (int*) calloc(n, sizeof(int));

    srand(seed);
    for(int i = 0; i < n; i++) {
        vector[i] = random_32bits() % max;
    }
    return vector;
}

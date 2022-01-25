#pragma once

typedef struct ABB{
    struct ABB* esq;
    struct ABB* dir;
    int chave;
}ABB;

ABB* ABB_Buscar(ABB* A, int chave);
ABB* ABB_Criar(int chave, ABB* esq, ABB* dir);
void ABB_Inserir(ABB** A, int chave);
void ABB_Imprimir(ABB* A, int b, char tipo);
void ABB_Remover(ABB** A, int chave);
float ABB_Sort(int* v, int n);
int* random_vector(int n, int max, int seed);
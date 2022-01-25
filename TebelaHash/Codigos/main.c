#include "ilist.h"
#include "hashTable.h"
#include "atividade.h"

#include <stdio.h>

#define M 11
#define N 100000

int main() {
    // THED* th = inserir_n_aleatorios(N, M, 42);
    THED* th;
    for(int i = 0; i < N; i++) {
        THED_Inserir(th, i, i);
    }

    for(int i = 0; i < M; i++) {
        printf("Tamanho %d: %d\n", i, ILIST_Tamanho(th->t[i]));
    }

    int maior = THED_MaisLonga(th);
    printf("Maior: %d\n", maior);

    int menor = THED_MaisCurta(th);
    printf("Menor: %d\n", menor);

    float media = THED_TamMedio(th);
    printf("Medio: %.0f\n", media);
}
#include "hashTable.h"
#include "ilist.h"
#include <stdlib.h>

unsigned int random_32bits() {
    unsigned int x;
   
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;

    return x;
}

THED* inserir_n_aleatorios(int n, int m, int seed) {
    THED* tabela = THED_Criar(m, n);

    srand(seed);
    for(int i = 0; i < n; i++) {
        int valor = random_32bits() % (10 * n);
        THED_Inserir(tabela, valor, i);
    }

    return tabela;
}

int THED_MaisLonga(THED* TH) {
    int maior = 0;
    for(int i = 0; i < TH->m; i++) {
        int tam = ILIST_Tamanho(TH->t[i]);
        if(tam > maior) {
            maior = tam;
        }
    }

    return maior;
}

int THED_MaisCurta(THED* TH) {
    int menor = INT_MAX;
    for(int i = 0; i < TH->m; i++) {
        int tam = ILIST_Tamanho(TH->t[i]);
        if(tam < menor) {
            menor = tam;
        }
    }

    return menor;
}

float THED_TamMedio(THED* TH) {
    int soma = 0;
    for(int i = 0; i < TH->m; i++) {
        soma += ILIST_Tamanho(TH->t[i]);
    }
    float media = soma / TH->m;

    return media;
}
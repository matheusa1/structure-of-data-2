#include "casca.h"
#include "struct.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){


    int tamArqEntrada =  256000;
    int maxBytes = 8388608;
    int tambufferSaida = maxBytes / 8;
    const char* arq = "teste1.dat";

    clock_t t = clock();

    ordenacaoExterna(arq, tamArqEntrada, maxBytes, tambufferSaida, "saidaFinal.dat");

    t = clock() - t;

    printf("%f sec\n", ((float)t)/CLOCKS_PER_SEC);





    int n = 256000;
    const char* fname = "saidaFinal.dat";
    ITEM_VENDA* v = malloc(sizeof(ITEM_VENDA) * n);
    FILE* arq1 = fopen(fname, "rb");
    fread(v, sizeof(ITEM_VENDA), n, arq1);
    fclose(arq1);
    int i;
    for(i = 1; i < n; i++){
        printf("%d %d\n", v[i-1].id, v[i].id);
        if(v[i-1].id > v[i].id){
            printf("O arq1uivo não está ordenado! A v[%d]>v[%d]!\n", i-1, i);
            exit(EXIT_FAILURE);
        }
    }
    printf("O arq1uivo está ordenado!\n");
    free(v);
    exit(EXIT_SUCCESS);
}
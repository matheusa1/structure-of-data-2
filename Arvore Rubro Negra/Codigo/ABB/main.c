#include "ABB.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#define SIZE 500000

int main() {
    // int vetor[SIZE];
    // for(int i = 0; i < SIZE; i++) vetor[i] = SIZE - i - 1;
    
    // clock_t t;
    // t = clock();
    // ABB_Sort(vetor, SIZE);
    // t = clock() - t;

    // printf("%f sec", ((float)t)/CLOCKS_PER_SEC);

    int* vetor;
    float res[10];
    float size[10];
    for(int i = 1; i <= 10; i++) {
        vetor = random_vector(SIZE, 10 * SIZE, i*10);

        clock_t t;
        t = clock();
        size[i - 1] = ABB_Sort(vetor, SIZE);
        t = clock() - t;

        // printf("%d: %f sec\n", i, ((float)t)/CLOCKS_PER_SEC);
        res[i - 1] = ((float)t)/CLOCKS_PER_SEC;
    }

    float mediaTempo = 0;
    float dpTempo = 0;
    float mediaSize = 0;
    float dpSize = 0;

    for(int i = 0; i < 10; i++) {
        mediaTempo += res[i];
    }
    mediaTempo /= 10;

    for(int i = 0; i < 10; i++) {
        dpTempo += pow(res[i] - mediaTempo, 2);
    }
    dpTempo /= 10;

    for(int i = 0; i < 10; i++) {
        mediaSize += size[i];
    }
    mediaSize /= 10;

    for(int i = 0; i < 10; i++) {
        dpSize += pow(size[i] - mediaSize, 2);
    }
    dpSize /= 10;

    printf("media tempo: %f\n", mediaTempo);
    printf("desvio padrao tempo: %f\n", dpTempo);
    printf("media tamanho: %f\n", mediaSize);
    printf("desvio padrao tamanho: %f\n", dpSize);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50000

int* random_vector(int n, int max, int seed);
int partition(int* vetor, int p, int r);
int partition_randomizado(int* vetor, int p, int r);
int partition_mediana(int* vetor, int p, int r);
void troca(int* vetor, int i, int j);
void quickSort(int* vetor, int e, int d);
void quickSort_randomizado(int* vetor, int e, int d);
void quickSort_mediana(int* vetor, int e, int d);
unsigned int random_32bits();

int main(){

    int* vetor = random_vector(SIZE, 100 * SIZE, 42);
    // int vetor[SIZE];
    // for(int i = 0; i < SIZE; i++) vetor[i] = i + 1;

    // printf("Vetor original: [ ");
    // for(int i = 0; i < SIZE; i++) {
    //     printf("%d ", vetor[i]);
    // }
    // printf("]\n");

    // clock_t t;
    // t = clock();

    // quickSort(vetor, 0, SIZE - 1);
    // quickSort_randomizado(vetor, 0, SIZE - 1);
    quickSort_mediana(vetor, 0, SIZE - 1);

    // t = clock() - t;

    // printf("Vetor ordenado: [ ");
    // for(int i = 0; i < SIZE; i++) {
    //     printf("%d ", vetor[i]);
    // }
    // printf("]\n");

    // printf ("%f seconds\n", ((float) t) / CLOCKS_PER_SEC);

    return 0;
}

int partition(int* vetor, int p, int r) {
    int x;
    int i, j;
    x = vetor[r];
    i = p - 1;
    for(j = p; j < r; j++) {
        if(vetor[j] <= x) {
            i++;
            troca(vetor, i, j);
        }
    }
    troca(vetor, i + 1, r);

    return i + 1;
}

int partition_randomizado(int* vetor, int p, int r) {
    int x;
    int i, j;
    int random = p + (rand() % (r - p) + 1);
    troca(vetor, random, r);

    x = vetor[r];
    i = p - 1;
    for(j = p; j < r; j++) {
        if(vetor[j] <= x) {
            i++;
            troca(vetor, i, j);
        }
    }
    troca(vetor, i + 1, r);

    return i + 1;
}

int partition_mediana(int* vetor, int p, int r) {
    int x;
    int i, j;
    int mediana = (p + r)/2;
    if(vetor[mediana] > vetor[p] && vetor[mediana] < vetor[r]) troca(vetor, mediana, r);
    if(vetor[p] > vetor[mediana] && vetor[p] < vetor[r]) troca(vetor, p, r);

    x = vetor[r];
    i = p - 1;
    for(j = p; j < r; j++) {
        if(vetor[j] <= x) {
            i++;
            troca(vetor, i, j);
        }
    }
    troca(vetor, i + 1, r);

    return i + 1;
}

void troca(int* vetor, int i, int j) {
    int temp = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = temp;
}

void quickSort(int* vetor, int e, int d) {
    int q;
    if(e < d) {
        q = partition(vetor, e, d);
        quickSort(vetor, e, q - 1);
        quickSort(vetor, q + 1, d);
    }
}

void quickSort_randomizado(int* vetor, int e, int d) {
    int q;
    if(e < d) {
        q = partition_randomizado(vetor, e, d);
        quickSort(vetor, e, q - 1);
        quickSort(vetor, q + 1, d);
    }
}

void quickSort_mediana(int* vetor, int e, int d) {
    int q;
    if(e < d) {
        q = partition_mediana(vetor, e, d);
        quickSort(vetor, e, q - 1);
        quickSort(vetor, q + 1, d);
    }
}

int* random_vector(int n, int max, int seed) {
    int* vector = (int*) calloc(n, sizeof(int));

    srand(seed);
    for(int i = 0; i < n; i++) {
        vector[i] = random_32bits() % max;
    }
    return vector;
}

unsigned int random_32bits(){
    unsigned int x;
   
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;

    return x;
}
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 1000000
#define K SIZE

int* random_vector_unique_elems(int n, int seed);
int smallerSearch(int* vector, int start, int end);
int biggerSearch(int* vector, int start, int end);
unsigned int random_32bits();

int SelectionMinK(int* vector, int size, int k);
void SelectionSortK(int* vector, int size, int k);
void switchPosition(int* vector, int pos1, int pos2);

int QuickMinK(int* vector, int left, int right, int k);
void QuickSortK(int* vector, int left, int right, int k, int* flag);
int partition(int* vector, int start, int end);

int main() {
    int* vector = random_vector_unique_elems(SIZE, 42);

    // for(int i = 0; i < SIZE; i++) printf("%d ", vector[i]);
    
    clock_t t;

    // t = clock();
    // int res = SelectionMinK(vector, SIZE, K);
    // t = clock() - t;
    // printf("Tempo SelectionMinK: %f\n", ((float)t)/CLOCKS_PER_SEC);

    t = clock();
    int res = QuickMinK(vector, 0, SIZE - 1, K);
    t = clock() - t;

    printf("%do menor valor: %d\n", K, res);
    printf("Tempo QuickMinK: %f\n", ((float)t)/CLOCKS_PER_SEC);

    free(vector);
    vector = NULL;
    return 0;
}

int* random_vector_unique_elems(int n, int seed) {
    int* vector = (int*) calloc (n, sizeof(int));
    for(int i = 0; i < n; i++) vector[i] = i;
    for(int i = 0; i < n; i++) switchPosition(vector, i, random_32bits() % SIZE);

    return vector;
}

int smallerSearch(int* vector, int start, int end) {
    int smaller = start;
    for(int i = start; i < end; i++) {
        if(vector[i] < vector[smaller]) smaller = i;
    }
    return smaller;
}

int biggerSearch(int* vector, int start, int end) {
    int bigger = start;
    for(int i = start; i < end; i++) {
        if(vector[i] > vector[bigger]) bigger = i;
    }
    return bigger;
}

unsigned int random_32bits() {
    unsigned int x;
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;
    return x;
}

int SelectionMinK(int* vector, int size, int k) {
    if(k > size) return vector[smallerSearch(vector, 0, size)];
    SelectionSortK(vector, size, k);

    return vector[k - 1];
}

void SelectionSortK(int* vector, int size, int k) {
    int smaller;
    int i = 0;
    while(i < k) {
        smaller = smallerSearch(vector, i, size);
        switchPosition(vector, i, smaller);
        i++;
    }
}

void switchPosition(int* vector, int pos1, int pos2) {
    int temp = vector[pos1];
    vector[pos1] = vector[pos2];
    vector[pos2] = temp;
}

int QuickMinK(int* vector, int left, int right, int k) {
    if(k > right) return vector[biggerSearch(vector, left, right)];

    int flag = 0;
    QuickSortK(vector, left, right, k, &flag);

    return vector[k - 1];
}

void QuickSortK(int* vector, int left, int right, int k, int* flag) {
    int q;
    if(left < right) {
        q = partition(vector, left, right);
        if(q == k) {
            *flag = 1;
            return;
        }
        QuickSortK(vector, left, q - 1, k, flag);
        if(*flag == 1) return;
        QuickSortK(vector, q + 1, right, k, flag);
        if(*flag == 1) return;
    }
}

int partition(int* vector, int start, int end) {
    int x;
    int i, j;
    x = vector[end];
    i = start - 1;
    for(j = start; j < end; j++) {
        if(vector[j] <= x) {
            i++;
            switchPosition(vector, i, j);
        }
    }
    switchPosition(vector, i + 1, end);

    return i + 1;
}
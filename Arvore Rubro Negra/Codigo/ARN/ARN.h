#pragma once

#define TypeData int

typedef enum {
    C_RED,
    C_BLACK
} ArnColor;

typedef struct arn {
    struct arn* left;
    struct arn* right;
    int data;
    ArnColor color;
} Arn;

void arnInsert(Arn** A, int data);
void arnPrint(Arn* A, int size, char position);
float ARN_Sort(int* v, int n);
int* random_vector(int n, int max, int seed);
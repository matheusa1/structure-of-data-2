#pragma once

#include "struct.h"

#define TypeData ITEM_VENDA

typedef enum {
    C_RED,
    C_BLACK
} ArnColor;

typedef struct arn {
    struct arn* left;
    struct arn* right;
    TypeData data;
    ArnColor color;
} Arn;

void ARN_Sort(TypeData* v, int n);
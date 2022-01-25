#pragma once
    
#include <stdio.h>

#include "struct.h"

typedef struct BufferSaida {
    ITEM_VENDA* buffer;
    FILE* arquivo;
    int quantidade;
    int marcador;
} BufferSaida;

BufferSaida* criar_BufferSaida(int quantidade, const char* arquivo);
void inserir_BufferSaida(BufferSaida* buffer, ITEM_VENDA item);
void despejar_BufferSaida(BufferSaida* buffer);
void destruir_BufferSaida(BufferSaida** enderecoBuffer);

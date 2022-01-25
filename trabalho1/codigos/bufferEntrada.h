#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "struct.h"

typedef struct bufferEntrada {
    ITEM_VENDA* array;
    FILE* arquivo;
    int quantidade;
    int marcador;
    int flag;
} BufferEntrada;

BufferEntrada* criar_bufferEntrada(int quantidade, const char* arquivo);
ITEM_VENDA proximo_bufferEntrada(BufferEntrada* buffer);
ITEM_VENDA consumir_bufferEntrada(BufferEntrada* buffer);
bool vazio_bufferEntrada(BufferEntrada* buffer);
void destruir_bufferEntrada(BufferEntrada** enderecoBuffer);
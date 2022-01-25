#include "bufferEntrada.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


void preencheVetor(BufferEntrada* buffer) {
    fread(buffer->array, sizeof(ITEM_VENDA), buffer->quantidade, buffer->arquivo);
}

BufferEntrada* criar_bufferEntrada(int quantidade, const char* arquivo) {
    BufferEntrada* buffer = (BufferEntrada*) malloc(sizeof(BufferEntrada));

    buffer->array = (ITEM_VENDA*) calloc(quantidade, sizeof(ITEM_VENDA));
    buffer->arquivo = fopen(arquivo, "rb");
    buffer->quantidade = quantidade;
    buffer->marcador = 0;
    buffer->flag = 0;

    preencheVetor(buffer);

    return buffer;
}

ITEM_VENDA proximo_bufferEntrada(BufferEntrada* buffer) {
    if(feof(buffer->arquivo)) {
        buffer->flag = 1;
        buffer->array[buffer->marcador].id = INT_MAX;
    }
    return buffer->array[buffer->marcador];
}

bool vazio_bufferEntrada(BufferEntrada* buffer) {
    return buffer->marcador == buffer->quantidade ? true : false;
}

ITEM_VENDA consumir_bufferEntrada(BufferEntrada* buffer) {
    if(vazio_bufferEntrada(buffer)) {
        preencheVetor(buffer);
        buffer->marcador = 0;
    }

    ITEM_VENDA item = buffer->array[buffer->marcador];
    buffer->marcador++;

    if(feof(buffer->arquivo)) {
        buffer->flag = 1;
        buffer->array[buffer->marcador].id = INT_MAX;
    }

    return item;
}

void destruir_bufferEntrada(BufferEntrada** enderecoBuffer) {
    BufferEntrada* tempBuffer = *enderecoBuffer;

    fclose(tempBuffer->arquivo);
    free(tempBuffer->array);
    free(tempBuffer);

    *enderecoBuffer = NULL;
}

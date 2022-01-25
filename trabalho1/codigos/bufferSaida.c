#include "bufferSaida.h"
#include "ARN.h"
#include <stdlib.h>
#include <stdbool.h>

bool bufferCheio(BufferSaida* buffer) {
    return buffer->quantidade == buffer->marcador ? true : false;
}

BufferSaida* criar_BufferSaida(int quantidade, const char* arquivo) {
    BufferSaida* buffer = (BufferSaida*) malloc(sizeof(BufferSaida));

    buffer->arquivo = fopen(arquivo, "wb");
    buffer->buffer = (ITEM_VENDA*) calloc(quantidade, sizeof(ITEM_VENDA));
    buffer->quantidade = quantidade;
    buffer->marcador = 0;

    return buffer;
}

void despejar_BufferSaida(BufferSaida* buffer) {
    ARN_Sort(buffer->buffer, buffer->quantidade);
    fwrite(buffer->buffer, sizeof(ITEM_VENDA), buffer->marcador, buffer->arquivo);
    buffer->marcador = 0;
}

void inserir_BufferSaida(BufferSaida* buffer, ITEM_VENDA item) {
    if(bufferCheio(buffer)) {
        despejar_BufferSaida(buffer);
    }
    
    buffer->buffer[buffer->marcador] = item;
    buffer->marcador++;
}

void destruir_BufferSaida(BufferSaida** enderecoBuffer) {
    BufferSaida* tempBuffer = *enderecoBuffer;

    // despejar_BufferSaida(tempBuffer);

    fclose(tempBuffer->arquivo);

    free(tempBuffer->buffer);
    free(tempBuffer);

    *enderecoBuffer = NULL;
}
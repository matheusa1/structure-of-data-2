#include "casca.h"
#include "k_vias.h"
#include "bufferEntrada.h"
#include "bufferSaida.h"
#include "ARN.h"
#include "struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void ordenacaoExterna(const char* arquivoEntrada, int tamEntrada, int maxBytes, int tamBuffer, const char* arquivoSaida) {
    FILE* arqEntrada = fopen(arquivoEntrada, "rb");

    int k = ceil((tamEntrada*1024 / (float) maxBytes));

    int tamArqTemp = tamEntrada / k;

    int tamBufferSaida = tamBuffer / 1024;
    int tamBufferEntrada = ((maxBytes - tamBuffer) / k) / 1024;
    printf("%d\n", tamBufferEntrada);

    int lidos;


    ITEM_VENDA* vetor = (ITEM_VENDA*) calloc(tamArqTemp, sizeof(ITEM_VENDA));

    char nome[30];
    for(int i = 0; i < k; i++) {
        lidos = fread(vetor, sizeof(ITEM_VENDA), tamArqTemp, arqEntrada);
        ARN_Sort(vetor, lidos);

        nome[0] = '\0';
        sprintf(nome, "%d", i);
        strcat(nome, ".dat");
        FILE* temp = fopen(nome, "wb");
        fwrite(vetor, sizeof(ITEM_VENDA), lidos, temp);
        fclose(temp);
    }
    free(vetor);
    vetor = NULL;

    fclose(arqEntrada);

    BufferEntrada** buffers = (BufferEntrada**) calloc(k, sizeof(BufferEntrada*));
    for(int i = 0; i < k; i++) {
        nome[0] = '\0';
        sprintf(nome, "%d", i);
        strcat(nome, ".dat");

        buffers[i] = criar_bufferEntrada(tamBufferEntrada, nome);
    }

    BufferSaida* saida = criar_BufferSaida(tamBufferSaida, arquivoSaida);

    k_vias(buffers, saida, k, tamEntrada);
    despejar_BufferSaida(saida);

    for(int i = 0; i < k; i++) {
        if(i == 0) destruir_BufferSaida(&saida);
        destruir_bufferEntrada(&buffers[i]);
        nome[0] = '\0';
        sprintf(nome, "%d", i);
        strcat(nome, ".dat");
        // remove(nome);
    }
    free(buffers);
    buffers = NULL;

}
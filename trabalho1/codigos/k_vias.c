#include "k_vias.h"
#include <stdlib.h>
#include <stdio.h>

void k_vias(BufferEntrada** entradas, BufferSaida* saida, int k, int quantidade) {
    BufferEntrada* menorId;
    ITEM_VENDA item;

    for(int j = 0; j < quantidade; j++) {
        int menor = INT_MAX;
        for(int i = 0; i < k; i++) {
            if (entradas[i]->flag == 0){
                if (menor > proximo_bufferEntrada(entradas[i]).id){
                    menor = proximo_bufferEntrada(entradas[i]).id;
                    menorId = entradas[i];
                }
            }
        }
        item = consumir_bufferEntrada(menorId);

        inserir_BufferSaida(saida, item);
    }
}
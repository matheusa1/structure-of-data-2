#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TIPO char*

typedef struct no {
    TIPO dado;
    struct no* proximo;
} No;

typedef struct pilha {
    No* topo;
    int quantidade;
} Pilha;


int** criaLabirinto(int n);
void destroiLabirinto(int*** enderecoLabirinto);
Pilha* criarPilha();
void destroiPilha(Pilha** enderecoPilha);
void adicionarPilha(Pilha* Pilha, TIPO dado);
bool removerPilha(Pilha* Pilha);
void pilhaToString(Pilha* Pilha, char* str);
void inverte_string(char* str);
void imprimeLabirinto(int** labirinto);
bool explorar(int** labirinto, Pilha* pilha);
bool explorar_r(int** labirinto, int x, int y, Pilha* pilha);

int main() {
    char str[100];
    Pilha* p1 = criarPilha();
    Pilha* p2 = criarPilha();
    Pilha* p3 = criarPilha();
    Pilha* p4 = criarPilha();

    int** A1 = criaLabirinto(1);
    int** A2 = criaLabirinto(2);
    int** A3 = criaLabirinto(3);
    int** A4 = criaLabirinto(4);

    imprimeLabirinto(A1);
    if(explorar(A1, p1)) printf("Tem caminho\n");
    else printf("Sem caminho\n");
    pilhaToString(p1, str);
    inverte_string(str);
    printf("Caminho percorrido: %s\n", str);

    
    imprimeLabirinto(A2);
    if(explorar(A2, p2)) printf("Tem caminho\n");
    else printf("Sem caminho\n");
    pilhaToString(p2, str);
    inverte_string(str);
    printf("Caminho percorrido: %s\n", str);

    imprimeLabirinto(A3);
    if(explorar(A3, p3)) printf("Tem caminho\n");
    else printf("Sem caminho\n");
    pilhaToString(p3, str);
    inverte_string(str);
    printf("Caminho percorrido: %s\n", str);

    imprimeLabirinto(A4);
    if(explorar(A4, p4)) printf("Tem caminho\n");
    else printf("Sem caminho\n");
    pilhaToString(p4, str);
    inverte_string(str);
    printf("Caminho percorrido: %s\n", str);

    destroiPilha(&p1);
    destroiPilha(&p2);
    destroiPilha(&p3);
    destroiPilha(&p4);
    

    return 0;
}

int** criaLabirinto(int n) { 
    int** temp = (int**) calloc(10, sizeof(int*));
    for(int i = 0; i < 10; i++) temp[i] = (int*) calloc(10, sizeof(int));

    if(n == 1) {
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                if(i == j || i == j + 1) temp[i][j] = 0;
                else temp[i][j] = 1;
            }
        }
    } 
    if(n == 2) {
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                if(i == 0 || j == 9) temp[i][j] = 0;
                else temp[i][j] = 1;
            }
        }
    }
    if(n == 3) {
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                temp[i][j] = 0;
            }
        }
    }
    if(n == 4) {
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                if(i == j || i == j + 1) temp[i][j] = 0;
                else temp[i][j] = 1;
            }
        }
        temp[9][8] = 1;

    }

    return temp;
}

void destroiLabirinto(int*** enderecoLabirinto) {
    int** temp = *enderecoLabirinto;
    for(int i = 0; i < 10; i++) {
        free(temp[i]);
    }
    free(temp);
    *enderecoLabirinto = NULL;
}

Pilha* criarPilha() {
    Pilha* temp = (Pilha*) malloc(sizeof(Pilha));

    No* x = (No*) malloc(sizeof(No));
    x->dado = "x";

    temp->topo = x;
    temp->quantidade = 0;

    return temp;
}

void destroiPilha(Pilha** enderecoPilha) {
    Pilha* temp = *enderecoPilha;
    while(temp->quantidade != 0) {
        removerPilha(temp);
    }
    free(temp);
    *enderecoPilha = NULL;
}

void adicionarPilha(Pilha* pilha, TIPO dado) {
    No* novoNo = (No*) malloc(sizeof(No));

    novoNo->dado = dado;
    novoNo->proximo = pilha->topo;

    pilha->topo = novoNo;

    pilha->quantidade++;
}

bool removerPilha(Pilha* pilha) {
    if(pilha->quantidade == 0) return false;

    No* temp = pilha->topo;
    pilha->topo = temp->proximo;

    free(temp);
    temp = NULL;

    pilha->quantidade--;

    return true;
}

void pilhaToString(Pilha* pilha, char* str) {

    No* aux = pilha->topo;
    str[0] = '\0';
    strcat(str, "[");

    for(int i = 0; i < pilha->quantidade; i++) {
        char temp[100];
        sprintf(temp, "%s", aux->dado);
        strcat(str, temp);
        if(i < pilha->quantidade - 1) strcat(str, ", ");
        aux = aux->proximo;
    }

    strcat(str, "]");
}

void inverte_string(char* str) {
    int tam = strlen(str);
    char save[tam];
    int cont = tam - 2;
    for(int i = 1; i < tam - 1; i++) {
        save[cont] = str[i];
        cont--;
    }
    for(int i = 1; i < tam - 1; i++) {
        str[i] = save[i];
    }
}

void imprimeLabirinto(int** labirinto) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            printf("%d ", labirinto[i][j]);
        }
        printf("\n");
    }
}

bool explorar(int** labirinto, Pilha* pilha) {
    int x = 0;
    int y = 0;

    if(explorar_r(labirinto, x, y, pilha)) return true;
    else return false;
}

bool explorar_r(int** labirinto, int x, int y, Pilha* pilha) {
    if(x == 9 && y == 9) return true;
    if(x < 0 || x > 9) return false;
    if(y < 0 || y > 9) return false;
    if(labirinto[x][y] == 1) return false;

    adicionarPilha(pilha, "s");
    if(pilha->topo->proximo->dado != "w" && explorar_r(labirinto, x + 1, y, pilha) == true) return true;
    else {
        removerPilha(pilha);
        adicionarPilha(pilha, "a");
        if(pilha->topo->proximo->dado != "d" && explorar_r(labirinto, x, y - 1, pilha) == true) return true;
        else {
            removerPilha(pilha);
            adicionarPilha(pilha, "d");
            if(pilha->topo->proximo->dado != "a" && explorar_r(labirinto, x, y + 1, pilha) == true) return true;
            
            else {
                removerPilha(pilha);
                adicionarPilha(pilha, "w");
                if(pilha->topo->proximo->dado != "s" && explorar_r(labirinto, x - 1, y, pilha) == true) return true;
                else {
                    removerPilha(pilha);
                    return false;
                }
            }
        }
    }

    return true;
}

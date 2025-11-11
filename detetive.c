#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50
#define HASH_SIZE 10

typedef struct Comodo {
    char nome[TAM];
    struct Comodo *esquerda, *direita;
} Comodo;

// Cria novo cômodo
Comodo* novoComodo(char *nome) {
    Comodo *novo = (Comodo*) malloc(sizeof(Comodo));
    strcpy(novo->nome, nome);
    novo->esquerda = novo->direita = NULL;
    return novo;
}

Comodo* inserirComodo(Comodo *raiz, char *nome) {
    if (raiz == NULL) return novoComodo(nome);
    if (strcmp(nome, raiz->nome) < 0)
        raiz->esquerda = inserirComodo(raiz->esquerda, nome);
    else if (strcmp(nome, raiz->nome) > 0)
        raiz->direita = inserirComodo(raiz->direita, nome);
    return raiz;
}

void exibirMapa(Comodo *raiz) {
    if (raiz != NULL) {
        exibirMapa(raiz->esquerda);
        printf("Cômodo: %s\n", raiz->nome);
        exibirMapa(raiz->direita);
    }
}

typedef struct Pista {
    char nome[TAM];
    struct Pista *esq, *dir;
} Pista;


Pista* novaPista(char *nome) {
    Pista *nova = (Pista*) malloc(sizeof(Pista));
    strcpy(nova->nome, nome);
    nova->esq = nova->dir = NULL;
    return nova;
}

Pista* inserirPista(Pista *raiz, char *nome) {
    if (raiz == NULL) return novaPista(nome);
    if (strcmp(nome, raiz->nome) < 0)
        raiz->esq = inserirPista(raiz->esq, nome);
    else if (strcmp(nome, raiz->nome) > 0)
        raiz->dir = inserirPista(raiz->dir, nome);
    return raiz;
}

// Exibir pistas (in-ordem)
void exibirPistas(Pista *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esq);
        printf("Pista: %s\n", raiz->nome);
        exibirPistas(raiz->dir);
    }
}

typedef struct Item {
    char pista[TAM];
    char suspeito[TAM];
    struct Item *prox;
} Item;

Item* tabela[HASH_SIZE];

int hash(char *str) {
    int soma = 0;
    for (int i = 0; str[i] != '\0'; i++)
        soma += str[i];
    return soma % HASH_SIZE;
}

void inserirHash(char *pista, char *suspeito) {
    int h = hash(pista);
    Item *novo = (Item*) malloc(sizeof(Item));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabela[h];
    tabela[h] = novo;
}

// Buscar suspeito por pista
char* buscarSuspeito(char *pista) {
    int h = hash(pista);
    Item *aux = tabela[h];
    while (aux != NULL) {
        if (strcmp(aux->pista, pista) == 0)
            return aux->suspeito;
        aux = aux->prox;
    }
    return "Suspeito não encontrado!";
}

// Exibir todas as relações
void exibirHash() {
    for (int i = 0; i < HASH_SIZE; i++) {
        Item *aux = tabela[i];
        while (aux != NULL) {
            printf("Pista: %-15s → Suspeito: %s\n", aux->pista, aux->suspeito);
            aux = aux->prox;
        }
    }
}

int main() {
    Comodo *mapa = NULL;
    mapa = inserirComodo(mapa, "Sala");
    mapa = inserirComodo(mapa, "Biblioteca");
    mapa = inserirComodo(mapa, "Cozinha");
    mapa = inserirComodo(mapa, "Jardim");
    mapa = inserirComodo(mapa, "Hall de Entrada");

    printf("=== Mapa da Mansão ===\n");
    exibirMapa(mapa);

    // Árvore de busca - Pistas
    Pista *pistas = NULL;
    pistas = inserirPista(pistas, "Pegada");
    pistas = inserirPista(pistas, "Castiçal");
    pistas = inserirPista(pistas, "Carta");
    pistas = inserirPista(pistas, "Luvas");
    pistas = inserirPista(pistas, "Relógio");

    printf("\n=== Pistas Coletadas ===\n");
    exibirPistas(pistas);

    // Tabela hash - Relação pista → suspeito
    inserirHash("Pegada", "Sr. Mostarda");
    inserirHash("Castiçal", "Sra. White");
    inserirHash("Carta", "Prof. Plum");
    inserirHash("Relógio", "Coronel Mustard");

    printf("\n=== Relações Pista → Suspeito ===\n");
    exibirHash();

    printf("\nExemplo de busca:\n");
    printf("Castiçal → %s\n", buscarSuspeito("Castiçal"));
    printf("Carta → %s\n", buscarSuspeito("Carta"));
    printf("Luvas → %s\n", buscarSuspeito("Luvas"));

    printf("\nFim da simulação. O detetive agora pode dizer o culpado!\n");
    return 0;
}

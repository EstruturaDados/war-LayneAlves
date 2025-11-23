
//PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO (VERSÃO DO EXERCÍCIO)

// OBJETIVOS DESTA ETAPA:
// - Implementar a struct Territorio
// - Cadastrar 5 territórios
// - Exibir os territórios cadastrados


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
#define MAX_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

// --- Estrutura de Dados ---
// Define um território com nome, cor do exército e número de tropas.
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
Territorio* alocarMapa();
void inicializarTerritorios(Territorio* mapa);
void exibirMapa(const Territorio* mapa);
void liberarMemoria(Territorio* mapa);
void limparBufferEntrada();

// --- Função Principal (main) ---
int main() {

    // 1. Configuração Inicial:
    //    Aloca memória para os territórios.
    Territorio* mapa = alocarMapa();
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa.\n");
        return 1;
    }

    // 2. Cadastro dos 5 territórios.
    inicializarTerritorios(mapa);

    // 3. Exibição dos territórios cadastrados.
    exibirMapa(mapa);

    // 4. Limpeza de memória.
    liberarMemoria(mapa);

    return 0;
}

// Implementação das Funções


// alocarMapa()
// Aloca dinamicamente um vetor de Territorio usando calloc.
Territorio* alocarMapa() {
    Territorio* ptr = (Territorio*) calloc(MAX_TERRITORIOS, sizeof(Territorio));
    return ptr;
}

// inicializarTerritorios()
// Pede ao usuário para preencher os dados dos 5 territórios.
void inicializarTerritorios(Territorio* mapa) {
    printf("\n= CADASTRO DE TERRITÓRIOS =\n");

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Digite o nome: ");
        scanf("%s", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Digite o número de tropas: ");
        scanf("%d", &mapa[i].tropas);

        limparBufferEntrada();
    }
}

// exibirMapa()
// Apenas exibe os dados dos territórios.
void exibirMapa(const Territorio* mapa) {
    printf("\n= TERRITÓRIOS REGISTRADOS =\n\n");

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

// liberarMemoria()
// Libera o vetor alocado.
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// limparBufferEntrada()
// Evita problemas ao usar scanf em sequência.
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

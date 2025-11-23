
// PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO (Nível Aventureiro)

// OBJETIVOS DESTA ETAPA:
// - Alocação dinâmica do número de territórios
// - Implementar funcionalidade de ataque entre territórios
// - Exibir os territórios após o ataque


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
#define TAM_NOME 30
#define TAM_COR 10

// --- Estrutura de Dados ---
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
Territorio* alocarMapa(int quantidade);
void inicializarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(const Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
void limparBufferEntrada();

// --- Função Principal (main) ---
int main() {
    srand(time(NULL)); // Garante aleatoriedade

    int n;

    // Pergunta quantos territórios devem ser cadastrados
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    limparBufferEntrada();

    // Alocação dinâmica
    Territorio* mapa = alocarMapa(n);
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Cadastro
    inicializarTerritorios(mapa, n);

    // Exibir antes do ataque
    exibirMapa(mapa, n);

    // Escolher atacante e defensor
    int a, d;
    printf("\nEscolha o número do território ATACANTE (1 a %d): ", n);
    scanf("%d", &a);

    printf("Escolha o número do território DEFENSOR (1 a %d): ", n);
    scanf("%d", &d);

    // Ajustar para índices
    a--;  
    d--;

    // Validação das cores
    if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
        printf("\nERRO: O atacante e o defensor pertencem ao mesmo exército!\n");
    } else {
        atacar(&mapa[a], &mapa[d]);
    }

    // Exibir estados atualizados
    exibirMapa(mapa, n);

    // Liberar memória
    liberarMemoria(mapa);

    return 0;
}

// Implementação das Funções


// Alocação dinâmica
Territorio* alocarMapa(int quantidade) {
    return (Territorio*) calloc(quantidade, sizeof(Territorio));
}

// Cadastro dos territórios
void inicializarTerritorios(Territorio* mapa, int quantidade) {
    printf("\n= CADASTRO DE TERRITÓRIOS =\n");

    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);

        limparBufferEntrada();
    }
}

// Exibição dos territórios
void exibirMapa(const Territorio* mapa, int quantidade) {
    printf("\n= ESTADO ATUAL DOS TERRITÓRIOS =\n");

    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------");
    }
    printf("\n");
}

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n\n===== FASE DE ATAQUE =====\n");

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("%s (%s) rola o dado e tira: %d\n",
           atacante->nome, atacante->cor, dadoAtacante);

    printf("%s (%s) rola o dado e tira: %d\n",
           defensor->nome, defensor->cor, dadoDefensor);

    // Resultado
    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante VENCEU o combate!\n");

        // Transferir cor
        strcpy(defensor->cor, atacante->cor);

        // Transferir metade das tropas
        defensor->tropas = atacante->tropas / 2;

        printf("%s agora pertence ao exército %s.\n",
               defensor->nome, defensor->cor);
    }
    else {
        printf("\nO defensor RESISTIU ao ataque!\n");

        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// Evitar problemas com buffer
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

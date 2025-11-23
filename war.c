// PROJETO WAR ESTRUTURADO - MISSÕES E ATAQUES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes ---
#define TAM_NOME 30
#define TAM_COR 10
#define MAX_MISSOES 5

// --- Estrutura do Território ---
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// --- Protótipos ---
Territorio* alocarMapa(int qtdTerritorios);
void inicializarTerritorios(Territorio* mapa, int qtdTerritorios);
void exibirMapa(const Territorio* mapa, int qtdTerritorios);
void liberarTerritorios(Territorio* mapa);
void limparBufferEntrada();
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
void exibirMissao(const char* missao);
void atacar(Territorio* atacante, Territorio* defensor);
int verificarMissao(const char* missao, Territorio* mapa, int qtdTerritorios);

// --- Função Principal ---
int main() {
    srand(time(NULL));

    int qtdTerritorios;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtdTerritorios);
    limparBufferEntrada();

    // Alocar território dinamicamente
    Territorio* mapa = alocarMapa(qtdTerritorios);
    if (!mapa) {
        printf("Erro ao alocar memória para os territórios.\n");
        return 1;
    }

    // Inicializar territórios
    inicializarTerritorios(mapa, qtdTerritorios);

    // Missões pré-definidas
    char* missoes[MAX_MISSOES] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor Vermelho",
        "Controlar ao menos 2 territorios com mais de 5 tropas",
        "Ter mais tropas que o inimigo em 2 territorios",
        "Controlar todos os territorios de cor Azul"
    };

    // Alocar dinamicamente a missão do jogador
    char* missaoJogador = (char*) malloc(200);
    if (!missaoJogador) {
        printf("Erro ao alocar memória para a missão.\n");
        liberarTerritorios(mapa);
        return 1;
    }

    // Sortear missão
    atribuirMissao(missaoJogador, missoes, MAX_MISSOES);

    // Exibir missão
    exibirMissao(missaoJogador);

    int opcao = -1;
    while (1) {
        exibirMapa(mapa, qtdTerritorios);

        printf("\nEscolha o numero do territorio ATACANTE (0 para sair): ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        if (opcao == 0) break;
        if (opcao < 1 || opcao > qtdTerritorios) {
            printf("Opcao invalida!\n");
            continue;
        }
        Territorio* atacante = &mapa[opcao - 1];

        printf("Escolha o numero do territorio DEFENSOR: ");
        int def;
        scanf("%d", &def);
        limparBufferEntrada();

        if (def < 1 || def > qtdTerritorios) {
            printf("Opcao invalida!\n");
            continue;
        }
        Territorio* defensor = &mapa[def - 1];

        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("ERRO: O atacante e o defensor pertencem ao mesmo exército!\n");
            continue;
        }

        // Executa ataque
        atacar(atacante, defensor);

        // Verifica missão
        if (verificarMissao(missaoJogador, mapa, qtdTerritorios)) {
            printf("\nPARABÉNS! Você cumpriu sua missão: %s\n", missaoJogador);
            break;
        }
    }

    // Limpeza de memória
    free(missaoJogador);
    liberarTerritorios(mapa);

    printf("Fim do jogo.\n");
    return 0;
}

// --- Implementações ---

Territorio* alocarMapa(int qtdTerritorios) {
    return (Territorio*) calloc(qtdTerritorios, sizeof(Territorio));
}

void inicializarTerritorios(Territorio* mapa, int qtdTerritorios) {
    printf("\n= CADASTRO DE TERRITÓRIOS =\n");
    for (int i = 0; i < qtdTerritorios; i++) {
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

void exibirMapa(const Territorio* mapa, int qtdTerritorios) {
    printf("\n= ESTADO ATUAL DOS TERRITÓRIOS =\n");
    for (int i = 0; i < qtdTerritorios; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

void liberarTerritorios(Territorio* mapa) {
    free(mapa);
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

void exibirMissao(const char* missao) {
    printf("\nSua missão é: %s\n\n", missao);
}

void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n%s (%s) rola o dado e tira: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("%s (%s) rola o dado e tira: %d\n", defensor->nome, defensor->cor, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante VENCEU o combate!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("O defensor RESISTIU ao ataque!\n");
        atacante->tropas = (atacante->tropas > 0) ? atacante->tropas - 1 : 0;
    }
}

int verificarMissao(const char* missao, Territorio* mapa, int qtdTerritorios) {
    // Lógica simplificada para demonstração
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        int consecutivos = 0;
        for (int i = 1; i < qtdTerritorios; i++) {
            if (strcmp(mapa[i].cor, mapa[i-1].cor) == 0)
                consecutivos++;
            else
                consecutivos = 0;

            if (consecutivos >= 2) return 1; // 3 consecutivos
        }
    }
    if (strcmp(missao, "Eliminar todas as tropas da cor Vermelho") == 0) {
        for (int i = 0; i < qtdTerritorios; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }
    if (strcmp(missao, "Controlar ao menos 2 territorios com mais de 5 tropas") == 0) {
        int count = 0;
        for (int i = 0; i < qtdTerritorios; i++) {
            if (mapa[i].tropas > 5)
                count++;
            if (count >= 2) return 1;
        }
    }
    if (strcmp(missao, "Ter mais tropas que o inimigo em 2 territorios") == 0) {
        int count = 0;
        for (int i = 0; i < qtdTerritorios; i++) {
            if (mapa[i].tropas > 5) count++; // simplificação
            if (count >= 2) return 1;
        }
    }
    if (strcmp(missao, "Controlar todos os territorios de cor Azul") == 0) {
        for (int i = 0; i < qtdTerritorios; i++) {
            if (strcmp(mapa[i].cor, "Azul") != 0)
                return 0;
        }
        return 1;
    }
    return 0;
}

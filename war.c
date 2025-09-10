#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Estrutura ---
typedef struct {
    char nome[50];
    char cor[50];
    int tropas;
} Territorio;

// --- Variaveis globais ---
Territorio* territorios = NULL;
int totalTerritorios = 0;

// --- Funcoes auxiliares ---
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void listarTerritorios() {
    printf("\n=====================================\n");
    printf("        MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=====================================\n");

    for (int i = 0; i < totalTerritorios; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n",
               i + 1,
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas);
    }
}

// --- Cadastro ---
void cadastrarTerritorios() {
    int qtd;
    printf("\nQuantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);
    limparBuffer();

    if (qtd <= 0) {
        printf("Quantidade invalida.\n");
        return;
    }

    // realocar memoria
    territorios = realloc(territorios, (totalTerritorios + qtd) * sizeof(Territorio));

    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", totalTerritorios + 1);
        printf("Nome do Territorio: ");
        fgets(territorios[totalTerritorios].nome, 50, stdin);
        territorios[totalTerritorios].nome[strcspn(territorios[totalTerritorios].nome, "\n")] = 0;

        printf("Cor do Exercito: ");
        fgets(territorios[totalTerritorios].cor, 50, stdin);
        territorios[totalTerritorios].cor[strcspn(territorios[totalTerritorios].cor, "\n")] = 0;

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[totalTerritorios].tropas);
        limparBuffer();

        totalTerritorios++;
    }

    printf("\nCadastro concluido com sucesso!\n");
}

// --- Fase de ataque ---
void faseAtaque() {
    if (totalTerritorios < 2) {
        printf("\nEh necessario pelo menos 2 territorios para atacar.\n");
        return;
    }

    int atacante, defensor;

    do {
        listarTerritorios();

        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", totalTerritorios);
        scanf("%d", &atacante);
        limparBuffer();

        if (atacante == 0) break;

        if (atacante < 1 || atacante > totalTerritorios) {
            printf("Territorio invalido.\n");
            continue;
        }

        if (territorios[atacante - 1].tropas < 1) {
            printf("O territorio %s nao tem tropas suficientes para atacar (precisa de pelo menos 1).\n",
                   territorios[atacante - 1].nome);
            continue;
        }

        printf("Escolha o territorio defensor (1 a %d, diferente do atacante): ", totalTerritorios);
        scanf("%d", &defensor);
        limparBuffer();

        if (defensor < 1 || defensor > totalTerritorios || defensor == atacante) {
            printf("Territorio invalido.\n");
            continue;
        }

        // Simulacao dos dados
        srand(time(NULL));
        int dadoAtq = rand() % 6 + 1;
        int dadoDef = rand() % 6 + 1;

        printf("\nDado do Atacante (%s): %d\n", territorios[atacante - 1].nome, dadoAtq);
        printf("Dado do Defensor (%s): %d\n", territorios[defensor - 1].nome, dadoDef);

        if (dadoAtq > dadoDef) {
            territorios[defensor - 1].tropas--;

            printf("\nVITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");

            if (territorios[defensor - 1].tropas <= 0) {
                printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n",
                       territorios[defensor - 1].nome,
                       territorios[atacante - 1].cor);

                // muda a cor
                strcpy(territorios[defensor - 1].cor, territorios[atacante - 1].cor);

                // tropas do conquistado = tropas do atacante - 1
                territorios[defensor - 1].tropas = territorios[atacante - 1].tropas - 1;

                // atacante fica com 1 tropa
                territorios[atacante - 1].tropas = 1;
            }
        } else {
            territorios[atacante - 1].tropas--;
            printf("\nDEFESA RESISTIU! O atacante perdeu 1 tropa.\n");
        }

        printf("\nPressione Enter para continuar para o proximo turno...");
        getchar();

    } while (1);
}

// --- Main ---
int main() {
    int opcao;

    do {
        printf("\n=====================================\n");
        printf("              WAR ESTRUTURADO\n");
        printf("=====================================\n");
        printf("1 - Cadastrar territorios\n");
        printf("2 - Exibir territorios\n");
        printf("3 - Fase de ataque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarTerritorios();
                break;
            case 2:
                listarTerritorios();
                break;
            case 3:
                faseAtaque();
                break;
            case 0:
                printf("\nJogo encerrado. Liberando memoria...\n");
                free(territorios);
                territorios = NULL;
                printf("Memoria liberada. Ate a proxima!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
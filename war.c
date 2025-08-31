#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
#define MAX_TERRITORIOS 5
#define TAM_STRING 50

struct Territorios{  
   char continente[TAM_STRING];
   char cor[TAM_STRING];
   int  tropas;

};

// --- Função para limpar buffer de entrada ---
void LimparBufferEntrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// --- Função principal ---
int main(){
    struct Territorios war[MAX_TERRITORIOS];
    int totalterritorios = 0;
    int opcao;
    
    do{

        printf("=====================================\n");
        printf("                 WAR\n");
        printf("=====================================\n");
        printf("1 - Cadastrar territorio\n");
        printf("2 - Exibir territorios cadastrados\n");
        printf("0 - Sair\n");
        printf("-------------------------------------\n");
        printf("Escolha uma opcao\n");

        scanf("%d", &opcao);
        LimparBufferEntrada();

        switch (opcao)
        {
        case 1:
           printf("--- Cadastro de Territorio ---\n");
           if (totalterritorios < MAX_TERRITORIOS){
              printf("Digite o nome do Continente: ");
              fgets( war[totalterritorios].continente, TAM_STRING, stdin);

              printf("Digite a Cor: ");
              fgets( war[totalterritorios].cor, TAM_STRING, stdin); 

              war[totalterritorios].continente[strcspn(war[totalterritorios].continente, "\n")] = '\0'; 
              war[totalterritorios].cor[strcspn(war[totalterritorios].cor, "\n")] = '\0'; 
               
              printf("Digite a quantidade de tropas:  ");
              scanf("%d", &war[totalterritorios].tropas);
              LimparBufferEntrada();

              totalterritorios++;

              printf("\nTerritorio Cadastrado com sucesso!\n");

           } else{
            printf("Quantidade maxima de territorios cadastrados completo!\n");
           }
        
           printf("\nPressione Enter para continuar...");
           getchar(); //Pausa para o usuário ler a mensagem antes de voltar ao manu
           break;

        case 2: //Listagem de Territorios
           printf("--- Lista de territorios cadastrados ---\n\n");

           if(totalterritorios == 0){
            printf("Nenhum territorio cadastrado.\n");
           } else{
            for (int i = 0; i< totalterritorios; i++){
                printf("----------------------------------\n");
                printf("Continente %d\n", i + 1);
                printf("Continente: %s\n", war[i].continente);
                printf("Cor: %s\n", war[i].cor);
                printf("Tropas: %d\n", war[i].tropas);
            }
             printf("----------------------------------\n");
           }
            
           printf("\nPressione Enter para continuar...");
           getchar();
           break;
           
        case 0:
           printf("\nSaindo do Sistema...\n");
           break;

           default:
            printf("\nOpcao invalida! Tente novamente.\n");
            printf("\nPressione Enter para continuar...");
            getchar();
            break;

        }

    } while (opcao !=0);
   
    return 0;
    
}
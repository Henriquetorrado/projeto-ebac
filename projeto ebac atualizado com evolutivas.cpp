#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Função para registrar um aluno
void registro() {
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];
    int continuar = 1;

    while (continuar) {
        printf("Digite o CPF a ser cadastrado: ");
        scanf("%s", cpf);

        strcpy(arquivo, cpf); // Copiar o CPF para usar como nome do arquivo

        FILE *file = fopen(arquivo, "w"); // Abrir o arquivo para escrita
        if (file == NULL) {
            perror("Erro ao abrir o arquivo");
            return;
        }
        fprintf(file, "%s,", cpf);

        printf("Digite o nome a ser cadastrado: ");
        scanf("%s", nome);
        fprintf(file, "%s,", nome);

        printf("Digite o sobrenome a ser cadastrado: ");
        scanf("%s", sobrenome);
        fprintf(file, "%s,", sobrenome);

        printf("Digite o cargo a ser cadastrado: ");
        scanf("%s", cargo);
        fprintf(file, "%s", cargo);

        fclose(file); // Fechar o arquivo

        printf("Cadastro realizado com sucesso!\n");
        
        printf("Deseja cadastrar outro aluno? (1-Sim, 0-Não): ");
        scanf("%d", &continuar);
    }
}

// Função para consultar alunos
void consulta() {
    char cpf[40];
    char linha[200];
    int continuar = 1;

    while (continuar) {
        printf("Digite o CPF do aluno a ser consultado: ");
        scanf("%s", cpf);

        FILE *file = fopen(cpf, "r"); // Abrir o arquivo para leitura
        if (file == NULL) {
            perror("Erro ao abrir o arquivo");
            return;
        }

        while (fgets(linha, sizeof(linha), file)) {
            printf("%s\n", linha);
        }
        fclose(file); // Fechar o arquivo

        printf("Deseja consultar outro aluno? (1-Sim, 0-Não): ");
        scanf("%d", &continuar);
    }
}

// Função para excluir alunos
void exclusao() {
    char cpf[40];
    int continuar = 1;

    while (continuar) {
        printf("Digite o CPF do aluno a ser excluído: ");
        scanf("%s", cpf);

        if (remove(cpf) == 0) {
            printf("Aluno excluído com sucesso!\n");
        } else {
            perror("Erro ao excluir o aluno");
        }

        printf("Deseja excluir outro aluno? (1-Sim, 0-Não): ");
        scanf("%d", &continuar);
    }
}

int main() {
    int opcao = 0;
    int running = 1; // Variável para controlar o loop principal

    setlocale(LC_ALL, "Portuguese"); // Definir a linguagem

    while (running) {
        // Limpar a tela (compatível com Windows e Unix)
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("### Registro de alunos EBAC ###\n\n");
        printf("Escolha a opção desejada:\n\n");
        printf("\t1 - Registro de alunos\n");
        printf("\t2 - Consultar alunos\n");
        printf("\t3 - Excluir alunos\n");
        printf("\t4 - Sair\n\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        // Limpar a tela
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        switch (opcao) {
            case 1:
                registro();
                break;
            case 2:
                consulta();
                break;
            case 3:
                exclusao();
                break;
            case 4:
                running = 0;
                break;
            default:
                printf("Opção indisponível\n");
                break;
        }

        // Pausar a execução (compatível com Windows e Unix)
        if (running) {
            printf("Pressione qualquer tecla para continuar...");
            getchar(); // Consumir o newline deixado pelo scanf
            getchar();
        }
    }

    return 0;
}


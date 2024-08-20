#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define SENHA_CORRETA "admin"  // Senha definida como "admin"

// Função para verificar a senha de acesso
int verificar_senha() {
    char senha[20];

    printf(" Login de adiministrador \n\n Digite a senha de acesso: ");
    scanf("%s", senha);

    if (strcmp(senha, SENHA_CORRETA) == 0) {
        printf("Acesso concedido!\n\n");
        return 1;
    } else {
        printf("Senha incorreta! Acesso negado.\n");
        return 0;
    }
}

// Função para registro de alunos
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

        strcpy(arquivo, cpf);

        FILE *file = fopen(arquivo, "w");
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

        fclose(file);

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

        FILE *file = fopen(cpf, "r");
        if (file == NULL) {
            perror("Erro ao abrir o arquivo");
            return;
        }

        while (fgets(linha, sizeof(linha), file)) {
            printf("%s\n", linha);
        }
        fclose(file);

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
    int running = 1;

    setlocale(LC_ALL, "Portuguese");

    if (!verificar_senha()) {
        return 0;  // Encerrar o programa se a senha estiver incorreta
    }

    while (running) {
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

        if (running) {
            printf("Pressione qualquer tecla para continuar...");
            getchar();
            getchar();
        }
    }

    return 0;
}


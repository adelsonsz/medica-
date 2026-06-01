#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nome[50];
    int quantidade;
    char dias[100];
    char horarios[100];
} Medicamento;

Medicamento meds[MAX];
int total = 0;

// ================= LIMPAR TELA =================
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// ================= SALVAR EM ARQUIVO =================
void salvarArquivo() {
    FILE *f = fopen("medicamentos.txt", "w");

    if (f == NULL) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(f, "Medicamento: %s\n", meds[i].nome);
        fprintf(f, "Quantidade: %d\n", meds[i].quantidade);
        fprintf(f, "Dias: %s\n", meds[i].dias);
        fprintf(f, "Horarios: %s\n", meds[i].horarios);
        fprintf(f, "--------------------------\n");
    }

    fclose(f);
}

// ================= CADASTRAR =================
void cadastrar() {
    limparTela();

    if (total >= MAX) {
        printf("Limite de cadastro atingido!\n");
        return;
    }

    printf("\n=== Cadastro de Medicamento ===\n");

    printf("Nome: ");
    scanf(" %[^\n]", meds[total].nome);

    printf("Quantidade: ");
    scanf("%d", &meds[total].quantidade);

    printf("Dias da semana: ");
    scanf(" %[^\n]", meds[total].dias);

    printf("Horarios (ex: 08:00, 14:00): ");
    scanf(" %[^\n]", meds[total].horarios);

    total++;

    salvarArquivo();

    printf("\nMedicamento cadastrado com sucesso!\n");
}

// ================= LISTAR =================
void listar() {
    limparTela();

    if (total == 0) {
        printf("Nenhum medicamento cadastrado.\n");
        return;
    }

    printf("\n=== Lista de Medicamentos ===\n");

    for (int i = 0; i < total; i++) {
        printf("%d - %s\n", i + 1, meds[i].nome);
    }

    int escolha;
    printf("\nEscolha um medicamento (0 para voltar): ");
    scanf("%d", &escolha);

    if (escolha > 0 && escolha <= total) {
        limparTela();

        Medicamento m = meds[escolha - 1];

        printf("\n=== Detalhes ===\n");
        printf("Nome: %s\n", m.nome);
        printf("Quantidade: %d\n", m.quantidade);
        printf("Dias: %s\n", m.dias);
        printf("Horarios: %s\n", m.horarios);
    }
}

// ================= BUSCAR HORÁRIOS =================
void buscarHorarios() {
    limparTela();

    if (total == 0) {
        printf("Nenhum medicamento cadastrado.\n");
        return;
    }

    printf("\n=== Horarios cadastrados ===\n");

    for (int i = 0; i < total; i++) {
        printf("%s -> %s\n", meds[i].nome, meds[i].horarios);
    }
}

// ================= MENU =================
int main() {
    int opcao;

    do {
        limparTela();

        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar medicamento\n");
        printf("2 - Listar medicamentos\n");
        printf("3 - Buscar por horarios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar();
                break;
            case 2:
                listar();
                break;
            case 3:
                buscarHorarios();
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
            getchar();
        }

    } while (opcao != 0);

    return 0;
}
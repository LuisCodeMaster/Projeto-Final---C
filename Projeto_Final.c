#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Prototipação das funções
void mostraOpcoes();
void criarConta();
void checarSaldo();
void depositar();
void sacar();
void transferencia();


typedef struct {
    int numeroConta;
    char nome[100];
    float saldo;
} ContaBancaria;

ContaBancaria contas[100]; 
int totalContas = 0; 

int main() {
    setlocale(LC_ALL, "portuguese"); 
    int op;

    mostraOpcoes(); 
    while(1) {
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar(); 

        switch(op) {
            case 1:
                criarConta();
                break;
            case 2:
                checarSaldo();
                break;
            case 3:
                depositar();
                break;
            case 4:
                sacar();
                break;
            case 5:
                transferencia();
                break;
            case 6:
                printf("Saindo do sistema...\n");
                exit(0);
            default:
                printf("Opção digitada é inválida. Tente novamente.\n");
        }
        mostraOpcoes(); 
    }

    return 0;
}

void mostraOpcoes() {
    printf("\n*****************************************\n");
    printf("*        Bem-vindo ao Banco APC         *\n");
    printf("*****************************************\n\n");
    printf("Por favor, selecione uma das opções abaixo para continuar:\n");
    printf("1 - Criar conta\n");
    printf("2 - Consultar saldo\n");
    printf("3 - Depósito\n");
    printf("4 - Saque\n");
    printf("5 - Transferência\n");
    printf("6 - Sair\n");
}

void criarConta() {
    if (totalContas >= 100) {
        printf("Não há como criar mais contas.\n");
        return;
    }
    ContaBancaria novaConta;
    novaConta.numeroConta = totalContas + 1;

    printf("Digite o nome do titular: ");
    fgets(novaConta.nome, 100, stdin);
    novaConta.nome[strcspn(novaConta.nome, "\n")] = 0; 

    novaConta.saldo = 0.0;
    contas[totalContas] = novaConta;
    totalContas++;
    
    system("clear || cls"); 
    printf("Sua conta foi criada com sucesso!\nO número da sua conta é: %d\n", novaConta.numeroConta);
}

void checarSaldo() {
    int numeroConta;
    
    printf("Digite o número da conta: ");
    scanf("%d", &numeroConta);

    for (int i = 0; i < totalContas; i++) {
        if (numeroConta == contas[i].numeroConta) {
            printf("Saldo da conta %d: R$ %.2f\n", contas[i].numeroConta, contas[i].saldo);
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

void depositar() {
    int numeroConta;
    float deposito;

    printf("Digite o número da conta: ");
    scanf("%d", &numeroConta);

    printf("Digite o valor do depósito: ");
    scanf("%f", &deposito);

    if (deposito < 0) {
        printf("O valor do depósito não pode ser negativo.\n");
        return;
    }

    for (int i = 0; i < totalContas; i++) {
        if (numeroConta == contas[i].numeroConta) {
            contas[i].saldo += deposito;
            printf("Depósito realizado com sucesso! Saldo atual da conta %d: R$ %.2f\n", contas[i].numeroConta, contas[i].saldo);
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

void sacar() {
    int numeroConta;
    float saque;

    printf("Digite o número da conta: ");
    scanf("%d", &numeroConta);

    printf("Digite o valor do saque: ");
    scanf("%f", &saque);

    if (saque < 0) {
        printf("O valor do saque não pode ser negativo.\n");
        return;
    }

    for (int i = 0; i < totalContas; i++) {
        if (numeroConta == contas[i].numeroConta) {
            if (saque <= contas[i].saldo) {
                contas[i].saldo -= saque;
                printf("Saque realizado com sucesso! Saldo atual da conta %d: R$ %.2f\n", contas[i].numeroConta, contas[i].saldo);
            } else {
                printf("Saldo insuficiente para realizar o saque.\n");
            }
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

void transferencia() {
    int co, cd;
    float valor;

    printf("Digite o número da conta de origem: ");
    scanf("%d", &co);

    printf("Digite o número da conta de destino: ");
    scanf("%d", &cd);

    if (cd == co) {
        printf("O número da conta de destino é o mesmo da origem.\n");
        return;
    }

    printf("Digite o valor a transferir: ");
    scanf("%f", &valor);

    if (valor < 0) {
        printf("O valor da transferência não pode ser negativo.\n");
        return;
    }

    int cai = -1;
    int cdi = -1;

    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numeroConta == co) {
            cai = i;
        }
        if (contas[i].numeroConta == cd) {
            cdi = i;
        }
    }

    if (cai == -1) {
        printf("Conta de origem não encontrada.\n");
        return;
    }
    if (cdi == -1) {
        printf("Conta de destino não encontrada.\n");
        return;
    }

    if (contas[cai].saldo >= valor) {
        contas[cai].saldo -= valor;
        contas[cdi].saldo += valor;
        printf("Transferência realizada com sucesso!\nSaldo da conta de origem %d: R$ %.2f\n", contas[cai].numeroConta, contas[cai].saldo);
    } else {
        printf("Saldo insuficiente na conta de origem.\n");
    }
}

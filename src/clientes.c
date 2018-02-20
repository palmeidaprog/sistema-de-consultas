/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "clientes.h"

void cadastrarCliente(char *cpf) {
    Cliente *cl = (Cliente *) malloc(sizeof(Cliente));
    
    
}

//--Validações----------------------------------------------------------------

int validaCPF(char *cpf) {
    size_t n = strlen(cpf);
    int primeiroDigito = 0, segundoDigito = 0, multiplicador = 11;

    for(size_t i = 0; i < n; ++i) {
        if(i <= 8) {
            primeiroDigito += (cpf[i] - '0') * (multiplicador - 1);
        }
            
        if(i <= 9) {
            segundoDigito += (cpf[i] - '0') * multiplicador;
        }

        if(cpf[i] < 48 || cpf[i] > 57) {
            return 0;
        }
        --multiplicador;
    }
    primeiroDigito = restoCPF(primeiroDigito);
    segundoDigito = restoCPF(segundoDigito);

    if(primeiroDigito != (cpf[9] - '0') || segundoDigito != (cpf[10] - '0')) {
        return 0;
    }

    return 1;
}

// função suporte de validaCPF()
int restoCPF(int x) {
    x = x * 10 / 11;
    return (x == 10) ? 0 : x;
} 

int validaNome(char *nome) {
    size_t n = strlen(nome);

    for(size_t i = 0; i < n; ++i) {
        if((nome[i] < 'A' || nome[i] > 'Z') && nome[i] != ' ' && 
            (nome[i] < 'a' || nome[i] > 'z')) {
            return 0;
        }
    }
    return 1;
}

int validaTelefone(char *telefone) {
    size_t n = strlen(telefone);

    for(size_t i = 0; i < n; ++i) {
        if(telefone[i] < 48 || telefone[i] > 57) {
            return 0;
        }
    }
    return 1;
}

//--Menu----------------------------------------------------------------------

int menuClientes() {
    int resp;

    printf("|==========================|\n");
    printf("|       Menu Clientes      |\n");
    printf("|                          |\n");
    printf("|  1 - Cadastrar           |\n");
    printf("|  2 - Voltar              |\n");
    printf("|                          |\n");
    printf("|==========================|\n\n");
    printf("Sua escolha: ");
    scanf("%d", &resp);
    limpaBuffer();

    return resp;
}

void loopClientes() {
    int m;
    int const VOLTAR = 2;
    char cpf[CPF_TAM];

    do {
        m = menuClientes();
        switch(m) {
            case 1:
                pegaString(cpf, CPF_TAM, CPF_MSG);
                if(validaCPF(cpf)) {
                    cadastrarCliente(cpf);
                }
                else {
                    printf("CPF Invalido\n\n");
                }
                break;
            case 2: 
                break;  
            default: 
                limpaTela();
                printf("Opcao invalida!\n");
                break;
        }
    } while(m != VOLTAR);
}

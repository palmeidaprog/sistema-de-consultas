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
    NoCliente *no;
    Cliente *cl = (Cliente *) malloc(sizeof(Cliente));

    strcpy(cl->cpf, cpf);
    pegaString(cl->nome, NOME_TAM, CLIENTE_NOME_MSG);
    pegaString(cl->telefone, TELEFONE_TAM, CLIENTE_TEL_MSG);
    pegaString(cl->email, EMAIL_TAM, CLIENTE_EMAIL_MSG);
    cl->status = 1;
    
    no = inserirCliente(cl);
    if(!no) {
        printf("ERRO: Nao foi possivel gravar no arquivo \"%s\"", 
            CLIENTE_ARQ);
        return ;
    }
    //inserirIndiceCliente(no);

}

//--Arvore--------------------------------------------------------------------

//--Arquivo-------------------------------------------------------------------

// retorna 1 se conseguiu incluir no arquivo
NoCliente *inserirCliente(Cliente *c) {
    FILE *arq;
    NoCliente *retorno = NULL;

    // criaar funcao para testar e criar arquivo

    arq = fopen(CLIENTE_ARQ, "ab");
    if(arq == NULL) {
        return NULL;    
    }

    if(fwrite(c, sizeof(Cliente), 1, arq) && ftell(arq) != -1){
        retorno = (NoCliente *) malloc(sizeof(NoCliente));
        retorno->dir = NULL;
        retorno->esq = NULL;
        strcpy(retorno->cpf, c->cpf);
        retorno->indice = ftell(arq) - sizeof(NoCliente);
        fflush(arq);
    }
    
    if(fclose(arq) != 0) {
        retorno = NULL;
    }

    return retorno;
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

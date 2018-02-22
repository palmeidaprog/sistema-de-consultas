/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "clientes.h"

void cadastrarCliente(NoCliente **raizCliente, char *cpf) {
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
    //inserirIndiceCliente(raizCliente, no);

}

//--Arvore--------------------------------------------------------------------

void criaArvoreCliente(NoCliente **raizCliente) {
    FILE *arq;
    int const TAM = 25;
    Cliente v[TAM], *c;
    NoCliente *no;
    long long pos = 0;
    
    arq = fopen(CLIENTE_ARQ, "rb");
    if(arq == NULL) {
        printf("Arquivo %s nao pode ser aberto.\n\n", CLIENTE_ARQ);
        return ;
    }

    while(fread(v, sizeof(Cliente), TAM, arq) == TAM) {
        for(int i = 0; i < TAM; i++) {
            no = criaNoCliente(&v[i], pos);
            inserirIndiceCliente(raizCliente, no);
            pos += sizeof(Cliente);
        }
    }

    while(fread(c, ))
}

void inserirIndiceCliente(NoCliente **raizCliente, NoCliente *no) {
    if(*raizCliente == NULL) { // arvore vazia
        raizCliente = no;
        return;
    }

    if(strcmp((*raizCliente)->cpf, no->cpf) > 0) {
        inserirIndiceCliente(&((*raizCliente)->esq), no);
    }
    else {
        inserirIndiceCliente(&((*raizCliente)->dir), no);
    }
}

NoCliente *criaNoCliente(Cliente *c, long long int pos) {
    NoCliente *no = NULL;
    
    if(pos < 0) {
        return NULL;
    }

    no = (NoCliente *) malloc(sizeof(NoCliente));
    no->dir = NULL;
    no->esq = NULL;
    strcpy(no->cpf, c->cpf);
    no->indice = pos; 
    return no;
}

//--Arquivo-------------------------------------------------------------------

// retorna 1 se conseguiu incluir no arquivo
NoCliente *inserirCliente(Cliente *c) {
    FILE *arq;
    NoCliente *retorno = NULL;

    arq = fopen(CLIENTE_ARQ, "ab");
    if(arq == NULL) {
        return NULL;    
    }
    
    if(fwrite(c, sizeof(Cliente), 1, arq) && ftell(arq) != -1){
        retorno = criaNoCliente(c, ftell(arq) - sizeof(NoCliente));
        fflush(arq); // força os dados a serem escritos
    }
    
    if(fclose(arq) != 0) { // nao conseguiu fechar arquivo
        free(retorno);
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

void loopClientes(NoCliente **raizCliente) {
    int m;
    int const VOLTAR = 2;
    char cpf[CPF_TAM];

    do {
        m = menuClientes();
        switch(m) {
            case 1:
                pegaString(cpf, CPF_TAM, CPF_MSG);
                if(validaCPF(cpf)) {
                    cadastrarCliente(raizCliente, cpf);
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

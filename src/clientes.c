/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "clientes.h"

void cadastrarCliente(FILE *arq, NoCliente **raizCliente, char *cpf) {
    NoCliente *no;
    Cliente *cl = (Cliente *) malloc(sizeof(Cliente));

    strcpy(cl->cpf, cpf);
    pegaString(cl->nome, NOME_TAM, CLIENTE_NOME_MSG);
    pegaString(cl->telefone, TELEFONE_TAM, CLIENTE_TEL_MSG);
    pegaString(cl->email, EMAIL_TAM, CLIENTE_EMAIL_MSG);
    cl->status = 1;
    
    no = escreveCliente(arq, cl);
    if(!no) {
        printf("ERRO: Nao foi possivel gravar no arquivo \"%s\"", 
            CLIENTE_ARQ);
        return ;
    }
    inserirIndiceCliente(raizCliente, no);

}

void exibirTodos(FILE *arq, NoCliente *raiz) {
    Cliente cliente;
    int pos = 0;

    if(raiz == NULL) {
        printf("Não existe clientes cadastrados\n\n");
    }

    if(ehFolha(raiz)) {
        leCliente(arq, raiz, &cliente);
        imprimeCliente(&cliente, pos);
        return ;
    }
    if(raiz->esq != NULL) {
        exibirTodos(arq, raiz->esq);
    }
    if(raiz->dir != NULL) {
        exibirTodos(arq, raiz->dir);
    }
}

//--Arvore--------------------------------------------------------------------

void criaArvoreCliente(FILE *arq, NoCliente **raizCliente) {
    int const TAM = 25;
    Cliente v[TAM];
    NoCliente *no;
    long long pos = 0, n;

    n = fread(v, sizeof(Cliente), TAM, arq);
    while(n > 0) {
        if(!feof(arq) && n != TAM) {
            printf("Erro de leitura no arquivo %s\n", CLIENTE_ARQ);
            return ;
        }
        for(int i = 0; i < n; i++) {
            no = criaNoCliente(&v[i], pos);
            inserirIndiceCliente(&(*raizCliente), no);
            ++pos;
        }
        n = fread(v, sizeof(Cliente), TAM, arq);
    }
}

void inserirIndiceCliente(NoCliente **raizCliente, NoCliente *no) {
    if(*raizCliente == NULL) { // arvore vazia
        *raizCliente = no;
        return;
    }

    if(strcmp((*raizCliente)->cpf, no->cpf) > 0) {
        inserirIndiceCliente(&((*raizCliente)->esq), no);
    } else {
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

int ehFolha(NoCliente *no) {
    if(no->dir == NULL && no->esq == NULL) {
        return 1;
    }
    return 0;
}

//--Arquivo-------------------------------------------------------------------

// retorna 1 se conseguiu incluir no arquivo
NoCliente *escreveCliente(FILE *arq, Cliente *c) {
    NoCliente *retorno = NULL;

    if(fwrite(c, sizeof(Cliente), 1, arq) && ftell(arq) != -1){
        retorno = criaNoCliente(c, (ftell(arq) - sizeof(NoCliente)) /
             sizeof(NoCliente));
        fflush(arq); // força os dados a serem escritos
    }
    return retorno;
}

// retorna 0 se nao conseguir ler
int leCliente(FILE *arq, NoCliente *no, Cliente *cliente) {
    fseek(arq, no->indice * sizeof(Cliente), SEEK_SET);
    if(fread(cliente, sizeof(Cliente), 1, arq) != 1) {
        return 0;
    }
    return 1;
}

//--Validações----------------------------------------------------------------

int validaCPF(char *cpf) {
    size_t n = strlen(cpf);
    int primeiroDigito = 0, segundoDigito = 0, multiplicador = 11;
    char cpfInvalidos[10][11] = { "00000000000", "11111111111", "22222222222", 
        "33333333333", "44444444444", "55555555555", "66666666666", 
        "77777777777", "88888888888", "99999999999"};

    if(n != 11) {
        return 0;
    }
    
    // verifica se todos digitos sao iguais
    for(int i = 0; i < 10; i++) {
        if(strcmp(cpfInvalidos[i], cpf) == 0) {
            return 0;
        }
    }

    for(size_t i = 0; i < n; ++i) {
        if(i <= 8) {
            primeiroDigito += (cpf[i] - '0') * (multiplicador - 1);
        }
            
        if(i <= 9) {
            segundoDigito += (cpf[i] - '0') * multiplicador;
        }

        if(cpf[i] < 48 || cpf[i] > 57) { // contem nao numeros
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
    x = x * 10 % 11;
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

//--io------------------------------------------------------------------------

void pegaCPF(char *cpf) {
    int erro = 0;
    
    do {    
        if(erro) {
            printf("CPF Invalido! ");
        }
        pegaString(cpf, CPF_TAM, "Digite o CPF: ");
        erro = 1;
    } while(!validaCPF(cpf));
}

void imprimeCliente(Cliente *c, int pos) {
    if(pos) { // so imprime se pos != 0
        printf("Cliente No. %d\n", pos);
    }
    printf("Nome: %s\n", c->nome);
    printf("CPF: %s\n", c->cpf);
    printf("Telefone: %s\n", c->telefone);
    printf("E-mail: %s\n\n", c->email);
}

//--Menu----------------------------------------------------------------------

int menuClientes() {
    int resp;

    printf("|=================================|\n");
    printf("|       Menu Clientes             |\n");
    printf("|                                 |\n");
    printf("|  1 - Cadastrar                  |\n");
    printf("|  2 - Imprime Todos Clientes     |\n");
    printf("|  3 - Voltar                     |\n");
    printf("|                                 |\n");
    printf("|=================================|\n\n");
    printf("Sua escolha: ");
    scanf("%d", &resp);
    limpaBuffer();

    return resp;
}

void loopClientes(FILE *arq, NoCliente **raizCliente) {
    int m;
    int const VOLTAR = 2;
    char cpf[CPF_TAM];

    do {
        m = menuClientes();
        switch(m) {
            case 1:
                pegaCPF(cpf);
                cadastrarCliente(arq, raizCliente, cpf);
                break;
            case 2: 
                limpaTela();
                exibirTodos(arq, *raizCliente);
                break;
            case 3:
                limpaTela();
                break;  
            default: 
                limpaTela();
                printf("Opcao invalida!\n");
                break;
        }
    } while(m != VOLTAR);
}

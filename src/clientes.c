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
    Cliente *cl;
    
    if(buscar(*raizCliente, cpf) != NULL) {
        printf("Cliente ja cadastrado\n\n");
        return ;
    }
    
    cl = criaCliente(cpf);
    no = escreveCliente(arq, cl, -1);
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
        return ;
    }

    if(ehFolha(raiz)) {
        leCliente(arq, raiz, &cliente);
        imprimeCliente(&cliente, ++pos);
        return ;
    }
    if(raiz->esq != NULL) {
        exibirTodos(arq, raiz->esq);
    }
    if(raiz->dir != NULL) {
        exibirTodos(arq, raiz->dir);
    }
}

void removerCliente(FILE *arq, NoCliente **raiz, char *cpf) {
    Cliente cliente;
    NoCliente *pos;

    pos = buscar(*raiz, cpf);
    if(pos == NULL) {
        printf("Cliente com esse CPF (%s) nao existe\n\n", cpf);
        return;
    }

    if(!leCliente(arq, pos, &cliente)) {
        printf("Erro ao ler o arquivo %s\n\n", CLIENTE_ARQ);
    }
    cliente.status = 0;
    escreveCliente(arq, &cliente, pos->indice * sizeof(Cliente));
    removerIndiceCliente(raiz, pos);
}

Cliente *criaCliente(char *cpf) {
    Cliente *cl = (Cliente *) malloc(sizeof(Cliente));

    strcpy(cl->cpf, cpf);
    // TODO: Resolver problema de ENTER no nome
    pegaDadoCliente(cl->nome, NOME);
    pegaDadoCliente(cl->telefone, TELEFONE);
    pegaDadoCliente(cl->email, EMAIL);
    cl->status = 1;

    return cl;
}

void alterarCliente(FILE *arq, NoCliente **raiz, char *cpf) {
    NoCliente *pos;
    Cliente cliente;

    pos = buscar(*raiz, cpf);
    if(pos == NULL) {
        printf("Cliente nao existe\n\n");
        return ;
    }

    if(!leCliente(arq, pos, &cliente)) {
        printf("Erro ao ler arquivo %s\n\n", CLIENTE_ARQ);
    }
    imprimeCliente(&cliente, 0);
    printf("Digite os novos dados:");
    pegaDadoCliente(cliente.telefone, TELEFONE);
    pegaDadoCliente(cliente.email, EMAIL);
    escreveCliente(arq, &cliente, pos->indice * sizeof(Cliente));
    printf("Dados modificados com exito\n\n");
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
            if(v[i].status) {
                no = criaNoCliente(&v[i], pos);
                inserirIndiceCliente(&(*raizCliente), no);
            }
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

    return ;
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

void removerIndiceCliente(NoCliente **raizCliente, NoCliente *remov) {
    NoCliente *maior;

    if(ehFolha(remov)) {
        removeFolhaCliente(raizCliente, remov);
    } else { // nao é folha
        maior = maiorIndiceCliente(*raizCliente);
        copiaNoCliente(remov, maior); // copia maior no lugar do removido
        if(!ehFolha(maior)) {
            moveNoCliente(maior, maior->esq); // move filho
        }
    }
}

void removeFolhaCliente(NoCliente **raiz, NoCliente *remov) {
    if(*raiz == remov) {
        free(*raiz);
        *raiz = NULL;
    } else if(strcmp(remov->cpf, (*raiz)->cpf) > 0) {
        removeFolhaCliente(&((*raiz)->dir), remov);
    } else {
        removeFolhaCliente(&((*raiz)->esq), remov);
    }
}

void copiaNoCliente(NoCliente *destino, NoCliente *origem) {
    strcpy(destino->cpf, origem->cpf);
    destino->indice = origem->indice;
}

void moveNoCliente(NoCliente *destino, NoCliente *origem) {
    copiaNoCliente(destino, origem);
    destino->esq = origem->esq;
    destino->dir = origem->dir;
    free(origem);
}

NoCliente *maiorIndiceCliente(NoCliente *raiz) {
    if(raiz == NULL) {
        return NULL;
    }

    while(!ehFolha(raiz)) {
        raiz = raiz->dir;
    }
    return raiz;
}

int ehFolha(NoCliente *no) {
    if(no->dir == NULL && no->esq == NULL) {
        return 1;
    }
    return 0;
}

NoCliente *buscar(NoCliente *raiz, char *cpf) {
    int cmp;

    if(raiz == NULL) {
        return NULL;
    }
    while(ehFolha(raiz)) {
        cmp = strcmp(cpf, raiz->cpf);
        if(cmp == 0) {
            return raiz;
        } else if(cmp > 0) {
            raiz = raiz->dir;
        } else {
            raiz = raiz->esq;
        }
    }
    return NULL;   
}

//--Arquivo-------------------------------------------------------------------

// retorna 1 se conseguiu incluir no arquivo
NoCliente *escreveCliente(FILE *arq, Cliente *c, int pos) {
    NoCliente *retorno = NULL;

    if(pos == -1) {
        fseek(arq, 0, SEEK_END);
    }
    else {
        fseek(arq, pos, SEEK_SET);
    }
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

void limpaArquivoCliente(FILE *arq) {
    FILE *aux;
    int const TAM = 25;
    int nLidos = 0, nEscrever = 0;
    Cliente lidos[TAM], escrever[TAM];

    aux = abreArquivo("aux.dat");
    fseek(arq, 0, SEEK_SET);
    do {
        nLidos = fread(lidos, sizeof(Cliente), TAM, arq);
        nEscrever = 0;
        for(int i = 0; i < nLidos; i++) {
            if(lidos[i].status) {
                escrever[nEscrever++] = lidos[i];
            }
        }

        if(nEscrever != fwrite(escrever, sizeof(Cliente), nEscrever, arq)) {
            printf("Erro ao executar limpeza no arquivo %s\n\n", CLIENTE_ARQ);
        }
    } while(nLidos == TAM);

    fechaArquivo(arq, CLIENTE_ARQ);
    fechaArquivo(aux, "aux.dat");
    remove(CLIENTE_ARQ);
    rename("aux.dat", CLIENTE_ARQ);
}

//--io------------------------------------------------------------------------

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
    printf("|  %d - Cadastrar                  |\n", CADASTRAR);
    printf("|  %d - Remover                    |\n", REMOVER);
    printf("|  %d - Alterar                    |\n", ALTERAR);
    printf("|  %d - Imprime Todos Clientes     |\n", EXIBIR_TODOS);
    printf("|  %d - Voltar                     |\n", VOLTAR);
    printf("|                                 |\n");
    printf("|=================================|\n\n");
    printf("Sua escolha: ");
    scanf("%d", &resp);
    limpaBuffer();

    return resp;
}

void loopClientes(FILE *arq, NoCliente **raizCliente) {
    int m;
    char cpf[CPF_TAM];

    do {
        m = menuClientes();
        switch(m) {
            case CADASTRAR:
                limpaTela();
                pegaDadoCliente(cpf, CPF);
                cadastrarCliente(arq, raizCliente, cpf);
                break;
            case REMOVER:
                limpaTela();
                pegaDadoCliente(cpf, CPF);
                removerCliente(arq, raizCliente, cpf);
                break;
            case EXIBIR_TODOS: 
                limpaTela();
                exibirTodos(arq, *raizCliente);
                break;
            case VOLTAR:
                limpaTela();
                break;  
            default: 
                limpaTela();
                printf("Opcao invalida!\n");
                break;
        }
    } while(m != VOLTAR);
}

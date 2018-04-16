/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "arvore_cliente.h"

void criaArvoreCliente(FILE *arq, NoCliente **raizCliente) {
    int const TAM = 25;
    Cliente v[25];
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
    } else if(remov->esq == NULL) {
        maior = remov->dir;
    } else {
        maior = maiorIndiceCliente(remov->esq);
    }
    copiaNoCliente(remov, maior); // copia maior no lugar do removido
    if(!ehFolha(maior)) {
        moveNoCliente(maior, maior->esq); // move filho
    } else {
        removeFolhaCliente(&remov, maior);
    }
}

void removeFolhaCliente(NoCliente **raiz, NoCliente *remov) {
    if(*raiz == remov) {
        free(*raiz);
        *raiz = NULL;
    } else if(strcmp(remov->cpf, (*raiz)->cpf) >= 0) {
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

    while(raiz->dir != NULL) {
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
    while(raiz != NULL) {
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

void desalocaClientes(NoCliente **raiz) {
    if(*raiz != NULL) {
        desalocaClientes(&((*raiz)->esq));
        desalocaClientes(&((*raiz)->dir));
        free(*raiz);
        *raiz = NULL;
    }
 } 
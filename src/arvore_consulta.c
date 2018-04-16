/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "arvore_consulta.h"

/* void criaArvoreConsulta(FILE *arq, NoConsulta **raizConsulta, int *codigo) {
    int const TAM = 100;
    Consulta v[100];
    NoConsulta *no;
    long long pos = 0, n;

    n = fread(v, sizeof(Consulta), TAM, arq);
    while(n > 0) {
        if(!feof(arq) && n != TAM) {
            printf("Erro de leitura no arquivo %s\n", CONSULTAS_ARQ);
            return ;
        }
        for(int i = 0; i < n; i++) {
            if(v[i].status == ATIVO) {
                no = criaNoConsulta(&v[i], pos, codigo);
                inserirIndiceConsulta(&(*raizConsulta), no);
            }
            ++pos;
        }
        n = fread(v, sizeof(Consulta), TAM, arq);
    }
}*/

void criaArvoreConsulta(FILE *arq, NoConsulta **raizConsulta, int *codigo) {
    Consulta c;
    NoConsulta *no;
    long long pos = 0, n;

    //n = fread(v, sizeof(Consulta), TAM, arq);
    fseek(arq, 0, SEEK_SET);
    while(1) {
        if(fread(&c, sizeof(Consulta), 1, arq) !=) {
            printf("Erro ao ler arquivo %s.\n\n", CONSULTAS_ARQ);
        }
        if(v[i].status == ATIVO) {
                if(comparaDatas())
                no = criaNoConsulta(&v[i], pos, codigo);
                inserirIndiceConsulta(&(*raizConsulta), no);
            }
            ++pos;
        }
        n = fread(v, sizeof(Consulta), TAM, arq);
    }
}

void inserirIndiceConsulta(NoConsulta **raizConsulta, NoConsulta *no) {
    if(*raizConsulta == NULL) { // arvore vazia
        *raizConsulta = no;
        return;
    }

    if(comparaDatas((*raizConsulta)->data, no->data) > 0 || 
        (comparaDatas((*raizConsulta)->data, no->data) == 0) && 
        (*raizConsulta)->codigo > no->codigo)) {
        inserirIndiceConsulta(&((*raizConsulta)->esq), no);
    } else {
        inserirIndiceConsulta(&((*raizConsulta)->dir), no);
    }

    return ;
}

NoConsulta *criaNoConsulta(Consulta *m, long long int pos) {
    NoConsulta *no = NULL;
    
    if(pos < 0) {
        return NULL;
    }
    no = (NoConsulta *) malloc(sizeof(NoConsulta));
    no->dir = NULL;
    no->esq = NULL;
    no->data = m->data;
    no->indice = pos;
    no->codigo = m->codigo;
    return no;
}

void removerIndiceConsulta(NoConsulta **raizConsulta, NoConsulta *remov) {
    NoConsulta *maior;

    if(ehFolhaConsulta(remov)) {
        removeFolhaConsulta(raizConsulta, remov);
    } else { // nao é folha
        maior = maiorIndiceConsulta(*raizConsulta);
        copiaNoConsulta(remov, maior); // copia maior no lugar do removido
        if(!ehFolhaConsulta(maior)) {
            moveNoConsulta(maior, maior->esq); // move filho
        } else {
            removeFolhaConsulta(raizConsulta, maior);
        }
    }
}

void removeFolhaConsulta(NoConsulta **raiz, NoConsulta *remov) {
    if(*raiz == remov) {
        free(*raiz);
        *raiz = NULL;
    } else if(strcmp(remov->crm, (*raiz)->crm) > 0) {
        removeFolhaConsulta(&((*raiz)->dir), remov);
    } else {
        removeFolhaConsulta(&((*raiz)->esq), remov);
    }
}

void copiaNoConsulta(NoConsulta *destino, NoConsulta *origem) {
    strcpy(destino->crm, origem->crm);
    destino->indice = origem->indice;
}

void moveNoConsulta(NoConsulta *destino, NoConsulta *origem) {
    copiaNoConsulta(destino, origem);
    destino->esq = origem->esq;
    destino->dir = origem->dir;
    free(origem);
}

NoConsulta *maiorIndiceConsulta(NoConsulta *raiz) {
    if(raiz == NULL) {
        return NULL;
    }

    while(raiz->dir != NULL) {
        raiz = raiz->dir;
    }
    return raiz;
}

int ehFolhaConsulta(NoConsulta *no) {
    if(no->dir == NULL && no->esq == NULL) {
        return 1;
    }
    return 0;
}

NoConsulta *buscarConsulta(NoConsulta *raiz, char *crm) {
    int cmp;

    if(raiz == NULL) {
        return NULL;
    }
    while(raiz != NULL) {
        cmp = strcmp(crm, raiz->crm);
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

void desalocaConsultas(NoConsulta **raiz) {
    if(*raiz != NULL) {
        desalocaConsultas(&((*raiz)->esq));
        desalocaConsultas(&((*raiz)->dir));
        free(*raiz);
        *raiz = NULL;
    }
}
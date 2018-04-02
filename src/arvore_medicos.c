/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "arvore_medicos.h"

void criaArvoreMedico(FILE *arq, NoMedico **raizMedico) {
    int const TAM = 100;
    Medico v[100];
    NoMedico *no;
    long long pos = 0, n;

    n = fread(v, sizeof(Medico), TAM, arq);
    while(n > 0) {
        if(!feof(arq) && n != TAM) {
            printf("Erro de leitura no arquivo %s\n", MEDICOS_ARQ);
            return ;
        }
        for(int i = 0; i < n; i++) {
            if(v[i].status) {
                no = criaNoMedico(&v[i], pos);
                inserirIndiceMedico(&(*raizMedico), no);
            }
            ++pos;
        }
        n = fread(v, sizeof(Medico), TAM, arq);
    }
}

void inserirIndiceMedico(NoMedico **raizMedico, NoMedico *no) {
    if(*raizMedico == NULL) { // arvore vazia
        *raizMedico = no;
        return;
    }

    if(strcmp((*raizMedico)->crm, no->crm) > 0) {
        inserirIndiceMedico(&((*raizMedico)->esq), no);
    } else {
        inserirIndiceMedico(&((*raizMedico)->dir), no);
    }

    return ;
}

NoMedico *criaNoMedico(Medico *m, long long int pos) {
    NoMedico *no = NULL;
    
    if(pos < 0) {
        return NULL;
    }
    no = (NoMedico *) malloc(sizeof(NoMedico));
    no->dir = NULL;
    no->esq = NULL;
    strcpy(no->crm, m->crm);
    no->indice = pos;
    return no;
}

void removerIndiceMedico(NoMedico **raizMedico, NoMedico *remov) {
    NoMedico *maior;

    if(ehFolhaMedico(remov)) {
        removeFolhaMedico(raizMedico, remov);
    } else { // nao é folha
        maior = maiorIndiceMedico(*raizMedico);
        copiaNoMedico(remov, maior); // copia maior no lugar do removido
        if(!ehFolhaMedico(maior)) {
            moveNoMedico(maior, maior->esq); // move filho
        } else {
            removeFolhaMedico(raizMedico, maior);
        }
    }
}

void removeFolhaMedico(NoMedico **raiz, NoMedico *remov) {
    if(*raiz == remov) {
        free(*raiz);
        *raiz = NULL;
    } else if(strcmp(remov->crm, (*raiz)->crm) > 0) {
        removeFolhaMedico(&((*raiz)->dir), remov);
    } else {
        removeFolhaMedico(&((*raiz)->esq), remov);
    }
}

void copiaNoMedico(NoMedico *destino, NoMedico *origem) {
    strcpy(destino->crm, origem->crm);
    destino->indice = origem->indice;
}

void moveNoMedico(NoMedico *destino, NoMedico *origem) {
    copiaNoMedico(destino, origem);
    destino->esq = origem->esq;
    destino->dir = origem->dir;
    free(origem);
}

NoMedico *maiorIndiceMedico(NoMedico *raiz) {
    if(raiz == NULL) {
        return NULL;
    }

    while(!ehFolhaMedico(raiz)) {
        raiz = raiz->dir;
    }
    return raiz;
}

int ehFolhaMedico(NoMedico *no) {
    if(no->dir == NULL && no->esq == NULL) {
        return 1;
    }
    return 0;
}

NoMedico *buscarMedico(NoMedico *raiz, char *crm) {
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

void desalocaMedicos(NoMedico **raiz) {
    if(*raiz != NULL) {
        desalocaMedicos(&((*raiz)->esq));
        desalocaMedicos(&((*raiz)->dir));
        free(*raiz);
        *raiz = NULL;
    }
}
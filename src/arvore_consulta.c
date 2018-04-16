/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "arvore_consulta.h"

void criaArvoreConsulta(FILE *arq, NoConsulta **raizConsulta, int *codigo) {
    Consulta c;
    Data hoje;
    NoConsulta *no;
    long long pos = 0;

    //n = fread(v, sizeof(Consulta), TAM, arq);
    fseek(arq, 0, SEEK_SET);
    hoje = pegaHoje();
    while(1) {
        if(fread(&c, sizeof(Consulta), 1, arq) != 1) {
            printf("Erro ao ler arquivo %s.\n\n", CONSULTAS_ARQ);
            break;
        }
        if(c.status == ATIVO || c.status == ESPERA) {
            if(comparaDatas(hoje, c.data) > 0) {
                c.status = ATENDIDO;
            } else {
                no = criaNoConsulta(&c, pos, codigo);
                inserirIndiceConsulta(&(*raizConsulta), no);
            }
            
            // regrava com info atualizada
            fseek(arq, -1 * (int) sizeof(Consulta), SEEK_CUR);
            if(fwrite(&c, sizeof(Consulta), 1, arq) != 1) {
                printf("Erro ao escrever o cliente no arquivo %s\n\n",
                    CONSULTAS_ARQ);
                    return;
            }   
        }
        ++pos;
    }

    if(!feof(arq)) {
        printf("Erro na leitura do arquivo %s.\n\n", CONSULTAS_ARQ);
    }
}

void inserirIndiceConsulta(NoConsulta **raizConsulta, NoConsulta *no) {
    if(*raizConsulta == NULL) { // arvore vazia
        *raizConsulta = no;
        return;
    }

    if(comparaDatas((*raizConsulta)->data, no->data) > 0 || 
        (comparaDatas((*raizConsulta)->data, no->data) == 0 && 
        (*raizConsulta)->codigo > no->codigo)) {
        inserirIndiceConsulta(&((*raizConsulta)->esq), no);
    } else {
        inserirIndiceConsulta(&((*raizConsulta)->dir), no);
    }
    return ;
}

// cria No e atualiza consulta com codigo novo
NoConsulta *criaNoConsulta(Consulta *c, long long int pos, int *codigo) {
    NoConsulta *no = NULL;
    
    if(pos < 0) {
        return NULL;
    }
    ++*codigo;
    no = (NoConsulta *) malloc(sizeof(NoConsulta));
    no->dir = NULL;
    no->esq = NULL;
    no->data = c->data;
    no->indice = pos;
    no->codigo = *codigo;
    c->codigo = *codigo;
    strcpy(no->medicoCrm, c->medicoCrm);
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
    } else if(comparaDatas(remov->data, (*raiz)->data) > 0 || 
            (comparaDatas(remov->data, (*raiz)->data) > 0 && remov->codigo > 
            (*raiz)->codigo)) {
        removeFolhaConsulta(&((*raiz)->dir), remov);
    } else {
        removeFolhaConsulta(&((*raiz)->esq), remov);
    }
}

void copiaNoConsulta(NoConsulta *destino, NoConsulta *origem) {
    destino->codigo = origem->codigo;
    destino->data = origem->data;
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

/*NoConsulta *buscarConsulta(NoConsulta *raiz, char *crm) {
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
}*/

// retorna 1 se o medico tem 10 ou mais consultas naquela data/turno
int medicoCheio(NoConsulta *raiz, Data data, char *crm) {
    int cont = 0, comp;
    while(raiz != NULL && cont < 10) {
        comp = comparaDatas(data, raiz->data);
        if(comp < 0) {
            raiz = raiz->esq;
        } else {
            if(comp == 0 && strcmp(crm, raiz->medicoCrm)) {
                ++cont;
            }
            raiz = raiz->dir;
        }
    }
    return (cont >= 10);
}

void desalocaConsultas(NoConsulta **raiz) {
    if(*raiz != NULL) {
        desalocaConsultas(&((*raiz)->esq));
        desalocaConsultas(&((*raiz)->dir));
        free(*raiz);
        *raiz = NULL;
    }
}
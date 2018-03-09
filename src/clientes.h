/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef CLIENTES_H
#define CLIENTES_H
 // mensagens para pegaString()

/*#define CPF_MSG "Insira o CPF (Sem pontos e hifen): "
#define CLIENTE_NOME_MSG "Insira o nome do cliente: "
#define CLIENTE_TEL_MSG "Insira o telefone do cliente: "
#define CLIENTE_EMAIL_MSG "Insira o e-mail do cliente: "*/

// menu constates
#define CADASTRAR 1
#define REMOVER 2
#define ALTERAR 3
#define EXIBIR_TODOS 4
#define VOLTAR 5

#include "io.h"
#include "clientesconstantes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//--Structs-------------------------------------------------------------------

typedef struct Cliente {
    char cpf[CPF_TAM];
    char nome[NOME_TAM];
    char telefone[TELEFONE_TAM];
    char email[EMAIL_TAM];
    int status;
} Cliente;

// No da arvore
typedef struct NoCliente {
    long long unsigned indice;
    char cpf[CPF_TAM];
    struct NoCliente *dir, *esq;
} NoCliente;

//----------------------------------------------------------------------------

void cadastrarCliente(FILE *arq, NoCliente **raizCliente, char *cpf);
void exibirTodos(FILE *arq, NoCliente *raizCliente);
void removerCliente(FILE *arq, NoCliente **raiz, char *cpf);
Cliente *criaCliente(char *cpf);
void alterarCliente(FILE *arq, NoCliente **raiz, char *cpf);

//--Arvore--------------------------------------------------------------------

void criaArvoreCliente(FILE *arq, NoCliente **raizCliente);
void inserirIndiceCliente(NoCliente **raizCliente, NoCliente *no);
void removerIndiceCliente(NoCliente **raizCliente, NoCliente *remov);
void removeFolhaCliente(NoCliente **raiz, NoCliente *remov);
void copiaNoCliente(NoCliente *destino, NoCliente *origem);
void moveNoCliente(NoCliente *destino, NoCliente *origem);
NoCliente *maiorIndiceCliente(NoCliente *raiz);
NoCliente *criaNoCliente(Cliente *c, long long int pos);
int ehFolha(NoCliente *no);
NoCliente *buscar(NoCliente *raiz, char *cpf);
int buscarRemover(NoCliente **raiz, NoCliente *anterior, NoCliente *remov, 
    char *cpf); // suporte para removeIndice

//--Arquivo-------------------------------------------------------------------

// se pos -1 escreve no final
NoCliente *escreveCliente(FILE *arq, Cliente *c, int pos);
int leCliente(FILE *arq, NoCliente *no, Cliente *cliente);
void limpaArquivoCliente(FILE *arq);

//--Validações----------------------------------------------------------------

int validaCPF(char *cpf);
int restoCPF(int x); 
int validaNome(char *nome);
int validaTelefone(char *telefone);
int ehEspaco(char c);
int ehNumero(char c);
int ehLetra(char c);
int validaEmail(char *email);
int validoNoEmail(char c);
int validacao(char *aValidar, ClienteTipo tipo);

//--io------------------------------------------------------------------------

void pegaDadoCliente(char *dado, ClienteTipo tipo);
void imprimeCliente(Cliente *c, int pos);

//--Menu----------------------------------------------------------------------

int menuClientes();
void loopClientes(FILE *arq, NoCliente **raizCliente);

#endif
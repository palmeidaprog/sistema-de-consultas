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

// Constantes
#define CPF_TAM 12 
#define NOME_TAM 128
#define TELEFONE_TAM 16
#define EMAIL_TAM 64
#define CLIENTE_ARQ "clientes.dat"

// mensagens para pegaString()

#define CPF_MSG "Insira o CPF (Sem pontos e hifen): "
#define CLIENTE_NOME_MSG "Insira o nome do cliente: "
#define CLIENTE_TEL_MSG "Insira o telefone do cliente: "
#define CLIENTE_EMAIL_MSG "Insira o e-mail do cliente: "

#include "io.h"
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

//--Arvore--------------------------------------------------------------------

void criaArvoreCliente(FILE *arq, NoCliente **raizCliente);
void inserirIndiceCliente(NoCliente **raizCliente, NoCliente *no);
NoCliente *criaNoCliente(Cliente *c, long long int pos);

//--Arquivo-------------------------------------------------------------------

NoCliente *escreveCliente(FILE *arq, Cliente *c);

//--Validações----------------------------------------------------------------

int validaCPF(char *cpf);
int restoCPF(int x); 
int validaNome(char *nome);
int validaTelefone(char *telefone);

//--io------------------------------------------------------------------------

void pegaCPF(char *cpf);

//--Menu----------------------------------------------------------------------

int menuClientes();
void loopClientes(FILE *arq, NoCliente **raizCliente);

#endif
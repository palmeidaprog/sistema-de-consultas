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
#define CPF_TAM 11 
#define NOME_TAM 128
#define TELEFONE_TAM 15
#define EMAIL_TAM 64
#define CLIENTE_ARQ "data/clientes.dat"

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
 
typedef struct CPFIndice {
    long long unsigned indice;
    char cpf[CPF_TAM];
} CPFIndice;

//----------------------------------------------------------------------------

void cadastraCliente();

//--Validações----------------------------------------------------------------

void cadastrarCliente(char *cpf);
int validaCPF(char *cpf);
int restoCPF(int x); 
int validaNome(char *nome);
int validaTelefone(char *telefone);
int menuClientes();
void loopClientes();

#endif
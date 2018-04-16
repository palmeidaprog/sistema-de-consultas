/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef CLIENTES_TYPES_H
#define CLIENTES_TYPES_H

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

#ifndef STRUCT_TAM
#define STRUCT_TAM

// Constantes
#define NOME_TAM 128
#define TELEFONE_TAM 17 // +1 para o /0
#define EMAIL_TAM 64

#endif // STRUCT_TAM

#define CPF_TAM 13 // + 1 para o /0
#define CPF_FORMAT 16

#define CLIENTE_ARQ "clientes.dat"

// tipo de clientes.h
typedef struct Cliente {
    char cpf[CPF_TAM];
    char nome[NOME_TAM];
    char telefone[TELEFONE_TAM];
    char email[EMAIL_TAM];
    int status;
} Cliente;

// tipo de arvore_cliente.h (No da arvore)
typedef struct NoCliente {
    long long unsigned indice;
    char cpf[CPF_TAM];
    struct NoCliente *dir, *esq;
} NoCliente;

// usado para validar CRM
typedef enum Estado {
    PE,
    PB
} Estado;

#endif // CLIENTES_TYPES_H
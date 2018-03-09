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

// Constantes
#define CPF_TAM 12 
#define NOME_TAM 128
#define TELEFONE_TAM 16
#define EMAIL_TAM 64
#define CLIENTE_ARQ "clientes.dat" // TODO funcao

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


#endif // CLIENTES_TYPES_H
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

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

// menu constates
#define CADASTRAR 1
#define REMOVER 2
#define ALTERAR 3
#define PROCURA_CPF 4
#define PROCURA_NOME 5
#define EXIBIR_TODOS 6
#define VOLTAR 7

#include "clientes_types.h"
#include "io.h"
#include "validacao.h"
#include "arvore_cliente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//----------------------------------------------------------------------------

void cadastrarCliente(FILE *arq, NoCliente **raizCliente, char *cpf);
void exibirTodos(FILE *arq, NoCliente *raizCliente, int *pos);
void removerCliente(FILE *arq, NoCliente **raiz, char *cpf);
Cliente *criaCliente(char *cpf);
void alterarCliente(FILE *arq, NoCliente **raiz, char *cpf);
void buscaNome(FILE *arq, char *nome);
void buscaCPF(FILE *arq, NoCliente *raiz, char *cpf);
int buscarCliente(FILE *arq, NoCliente *raiz, char *cpf, Cliente *cliente);

//--Arquivo-------------------------------------------------------------------

// se pos -1 escreve no final
NoCliente *escreveCliente(FILE *arq, Cliente *c, int pos);
int leCliente(FILE *arq, long int pos, Cliente *cliente);
void limpaArquivoCliente(FILE *arq);
int buscaPorNome(FILE *arq, char *nome);

//--io------------------------------------------------------------------------

void imprimeCliente(Cliente *c, int pos);
int validaProcuraCliente(int retorno);

//--Menu----------------------------------------------------------------------

int menuClientes();
void loopClientes(FILE *arq, NoCliente **raizCliente);

#endif
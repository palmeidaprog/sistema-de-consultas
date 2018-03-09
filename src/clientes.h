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

#include "clientes_types.h"
#include "io.h"
#include "validacao.h"
#include "arvore_cliente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//----------------------------------------------------------------------------

void cadastrarCliente(FILE *arq, NoCliente **raizCliente, char *cpf);
void exibirTodos(FILE *arq, NoCliente *raizCliente);
void removerCliente(FILE *arq, NoCliente **raiz, char *cpf);
Cliente *criaCliente(char *cpf);
void alterarCliente(FILE *arq, NoCliente **raiz, char *cpf);

//--Arquivo-------------------------------------------------------------------

// se pos -1 escreve no final
NoCliente *escreveCliente(FILE *arq, Cliente *c, int pos);
int leCliente(FILE *arq, NoCliente *no, Cliente *cliente);
void limpaArquivoCliente(FILE *arq);

//--io------------------------------------------------------------------------

void imprimeCliente(Cliente *c, int pos);

//--Menu----------------------------------------------------------------------

int menuClientes();
void loopClientes(FILE *arq, NoCliente **raizCliente);

#endif
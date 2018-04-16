/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef ARVORE_CLIENTE_H
#define ARVORE_CLIENTE_H

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

#include "clientes.h"
#include "validacao.h"
#include <stdlib.h>


//--Protótipos----------------------------------------------------------------

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
void desalocaClientes(NoCliente **raiz);

#endif // ARVORE_CLIENTE_H
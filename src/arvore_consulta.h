/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef ARVORE_CONSULTA_H
#define ARVORE_CONSULTA_H

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

#include "validacao.h"
#include "tempo.h"
#include "consultas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--Protótipos----------------------------------------------------------------

void criaArvoreConsulta(FILE *arq, NoConsulta **raizConsulta, int *codigo);
void inserirIndiceConsulta(NoConsulta **raizConsulta, NoConsulta *no);
void removerIndiceConsulta(NoConsulta **raizConsulta, NoConsulta *remov);
void removeFolhaConsulta(NoConsulta **raiz, NoConsulta *remov);
void copiaNoConsulta(NoConsulta *destino, NoConsulta *origem);
void moveNoConsulta(NoConsulta *destino, NoConsulta *origem);
NoConsulta *maiorIndiceConsulta(NoConsulta *raiz);
NoConsulta *criaNoConsulta(Consulta *m, long long int pos, int *codigo);
int ehFolhaConsulta(NoConsulta *no);
NoConsulta *buscarConsulta(NoConsulta *raiz, char *cpf);
int medicoCheio(NoConsulta *raiz, Data data, char *crm);
void desalocaConsultas(NoConsulta **raiz);

#endif // ARVORE_CONSULTA_H
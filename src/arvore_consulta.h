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
#include "consultas.h"
#include <stdio.h>
#include <string.h>

//--Protótipos----------------------------------------------------------------

void criaArvoreMedico(FILE *arqMed, NoMedico **raizMedico);
void inserirIndiceMedico(NoMedico **raizMedico, NoMedico *no);
void removerIndiceMedico(NoMedico **raizMedico, NoMedico *remov);
void removeFolhaMedico(NoMedico **raiz, NoMedico *remov);
void copiaNoMedico(NoMedico *destino, NoMedico *origem);
void moveNoMedico(NoMedico *destino, NoMedico *origem);
NoMedico *maiorIndiceMedico(NoMedico *raiz);
NoMedico *criaNoMedico(Medico *m, long long int pos);
int ehFolhaMedico(NoMedico *no);
NoMedico *buscarMedico(NoMedico *raiz, char *cpf);
void desalocaMedicos(NoMedico **raiz);

#endif // ARVORE_CONSULTA_H
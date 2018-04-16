/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef ARVORE_MEDICOS_H
#define ARVORE_MEDICOS_H

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

#include "medicos.h"
#include "validacao.h"
#include <stdio.h>
#include <stdlib.h>
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

#endif // ARVORE_MEDICOS_H
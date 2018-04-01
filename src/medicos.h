/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */


#ifndef MEDICOS_H
#define MEDICOS_H

// menu constantes
#define CADASTRAR_M 1
#define REMOVER_M 2
#define ALTERAR_M 3
#define PROCURA_CRM 4
#define PROCURA_NOME_M 5
#define EXIBIR_TODOS_M 6
#define VOLTAR_M 7

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif
#include "medicos_types.h"
#include "tempo.h"
#include "arvore_medicos.h"
#include "io.h"
#include <string.h>
#include <stdio.h>

void cadastrarMedico(FILE *arq, NoMedico **raizMedico, char *crm);
void exibirTodosMedicos(FILE *arq, NoMedico *raiz, int *pos);
void removerMedico(FILE *arq, NoMedico **raiz, char *crm);
Medico *criaMedico(char *crm);
void alterarMedico(FILE *arq, NoMedico **raiz, char *crm);
void buscaNomeMedico(FILE *arq, char *nome);

//--Arquivo-------------------------------------------------------------------

int buscaPorNomeMedico(FILE *arq, char *nome);
NoMedico *escreveMedico(FILE *arq, Medico *med, int pos);
int leMedico(FILE *arq, long long pos, Medico *medico);
void limpaArquivoMedico(FILE *arq);

//--io------------------------------------------------------------------------

void imprimeMedico(Medico *med, int pos);

//--Menu----------------------------------------------------------------------

int menuMedicos();
void loopMedicos(FILE *arqMed, NoMedico **raizMedico);

#endif // MEDICOS_H

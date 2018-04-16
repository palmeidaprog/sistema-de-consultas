/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef CONSULTAS_H
#define CONSULTAS_H

#include "consultas_types.h"
#include "arvore_consulta.h"
#include "medicos.h"
#include "clientes.h"
#include "validacao.h"
#include "tempo.h"

#define MARCAR_C 1
#define CONSULTAS_C 2
#define PACIENTES_C 3
#define DESMARCAR_C 4
#define VOLTAR_C 5

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

void marcarConsulta(FILE *arq, NoConsulta **raiz, Cliente *paciente, Medico 
            *medico, int *codigo);
void consultaMedico(FILE *arq, NoConsulta *raiz, Medico *medico);
void insereConsulta(FILE *arq, NoConsulta **raiz, Consulta *consulta, int 
            *codigo, char *msg);
int pegaPaciente(FILE *arqCliente, NoCliente *raizCliente, Cliente *cliente);
int pegaMedico(FILE *arqMedico, NoMedico *raizMedico, Medico *medico);
int buscaConsultaCRM(FILE *arq, NoConsulta *raiz, Data data, char *crm);
void desmarcaConsulta(FILE *arq, NoConsulta **raiz, NoConsulta *lido, char 
*cpf, char *crm);
void buscaConsultaPaciente(FILE *arq, NoConsulta *raiz, char *cpf);
void saiDaEspera(FILE *arq, NoConsulta *raiz, Data data, char *crm, char *cpf, 
            int *cont);
unsigned long indiceConsulta(NoConsulta *c);

//--Arquivo-------------------------------------------------------------------

NoConsulta *escreveConsulta(FILE *arq, Consulta *c, int pos, int *codigo);
int leConsulta(FILE *arq, long int pos, Consulta *cliente);

//--io------------------------------------------------------------------------

void imprimeConsulta(Consulta c, int pos);

//--Menu----------------------------------------------------------------------

int menuConsultas();
void loopConsultas(FILE *arqConsulta, FILE *arqCliente, FILE *arqMed, 
            NoConsulta **raizConsulta, NoCliente **raizCliente, NoMedico 
            **raizMedico, int *codigo);

#endif // CONSULTAS_H
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

#include "medicos.h"
#include "clientes.h"
#include "validacao.h"
#include "tempo.h"

#define MARCAR_C 1
#define PACIENTES_C 2
#define CONSULTAS_C 3
#define DESMARCAR_C 4
#define VOLTAR_C 5

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

int pegaPaciente(FILE *arqCliente, NoCliente *raizCliente, Cliente *cliente);
int pegaMedico(FILE *arqMedico, NoMedico *raizMedico, Medico *medico);

//--Menu----------------------------------------------------------------------

int menuMedicos();
void loopConsultas(FILE *arqCliente, FILE *arqMed, NoCliente **raizCliente, 
            NoMedico **raizMedico);

#endif // CONSULTAS_H
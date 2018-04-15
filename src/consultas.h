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

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

typedef struct Consulta {
    char clienteCpf[CPF_TAM];
    char medicoCrm[CRM];
    Data data;
    Turno turno;
    int n;
} Consulta;

#endif // CONSULTAS_H
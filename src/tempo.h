/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef TEMPO_H
#define TEMPO_H

#include "tempo_types.h"
#include "validacao.h"
#include <string.h>
#include <stdio.h>

void inicializarMatriz(Hora a[5][2]);
void imprimeTableHorario(Hora a[5][2]);

#endif // TEMPO_H
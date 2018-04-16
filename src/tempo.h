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

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

#include "tempo_types.h"
#include "validacao.h"
#include "io.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>

#define TEMPO_TAM 5
#define DATA_TAM 9

Data pegaData();
int parseData(char *str, Data *data);
Semana pegaDiaDaSemana(Data data);
void pegaDataTempo(char *str, size_t n);
void formataStdin(size_t n, size_t i);
int ultimoDiaMes(int mes);
int ehBissesto(int ano);
int validaData(Data data);
int validaTempo(Tempo tempo);
int comparaDatas(Data primeiro, Data segunda);

#endif // TEMPO_H
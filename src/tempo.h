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
#include <stdio.h>
#include <ctypes.h>

#define HORA_TAM 5
#define DATA_TAM 7

typedef enum Semana {
    DOMINGO ,
    SEGUNDA,
    TERCA = 1,
}


typedef struct Hora {
    int hora, min;
} Hora;

typedef struct Data {
    int dia, mes, ano, diaDaSemana;
} Data;


Data pegaData();
void pegaDataTempo(char *str, size_t n);
void formataStdin(size_t n, size_t i);
int ultimoDiaMes(int mes);
int ehBissesto(int ano);
int validaData(Data data);
int validaHora(Hora hora);
int comparaDatas(Data atual, Data data);


//void inicializarMatriz(Hora a[5][2]);
//void printHora(Hora hora);
//void preencherHorario(Hora a[5][2]);

#endif // TEMPO_H
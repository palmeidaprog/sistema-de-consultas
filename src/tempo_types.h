/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef TEMPO_TYPES_H
#define TEMPO_TYPES_H

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

typedef enum Turno {
    MANHA = 0,
    TARDE = 1
} Turno;

typedef enum Semana {
    DOMINGO,
    SEGUNDA,
    TERCA,
    QUARTA,
    QUINTA,
    SEXTA,
    SABADO
} Semana;

typedef struct Tempo {
    int hora, min;
} Tempo;

typedef struct Data {
    int dia, mes, ano;
    Semana diaDaSemana;
} Data;


#endif // TEMPO_TYPES_H
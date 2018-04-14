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

typedef struct Hora {
    int hora, min;
} Hora;

typedef struct Data {
    int dia, mes, ano;
} Data;



#endif // TEMPO_TYPES_H
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

typedef struct Hora {
    int hora, min, seg;
} Hora;

typedef struct Data {
    int dia, mes, ano;
    Hora hora;
} Data;

#endif // TEMPO_TYPES_H
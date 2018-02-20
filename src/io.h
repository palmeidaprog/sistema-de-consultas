/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CPF_MSG "Insira CPF (Sem pontos e hifen): "

void limpaBuffer();
void limpaTela();
void pegaString(char *str, size_t n, char *msg);

#endif // IO_H
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

void limpaBuffer();
void limpaTela();
void pegaString(char *str, size_t n, char *msg);
int existeArquivo(char *nomeDoArquivo);
void abreArquivo(char *nomeDoArquivo);
void fechaArquivo(FILE *f, char *nomeDoArquivo);

#endif // IO_H
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

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//nao é windows
#if !defined(Win32) && !defined(_Win32) && !defined(_WIN32) && !defined(_WIN64) 
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#else // windows
#include <conio.h>
#endif


void limpaBuffer();
void limpaTela();
void pegaCPF(char *str, size_t n);
void pegaString(char *str, size_t n);
int existeArquivo(char *nomeDoArquivo);
FILE *abreArquivo(char *nomeDoArquivo);
void fechaArquivo(FILE *f, char *nomeDoArquivo);

#endif // IO_H
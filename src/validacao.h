/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef VALIDACAO_H
#define VALIDACAO_H

#include "io.h"
#include <string.h>
#include <stdio.h>

typedef enum ClienteTipo {
    EMAIL,
    CPF,
    NOME,
    TELEFONE
} ClienteTipo;

int pegaTamanho(ClienteTipo tipo);
void pegaErro(ClienteTipo tipo, char *erro);
void pegaMensagem(ClienteTipo tipo, char *msg);
int pegaDadoCliente(char *dado, ClienteTipo tipo);

int validaCPF(char *cpf);
int restoCPF(int x); 
int validaNome(char *nome);
int validaTelefone(char *telefone);
int ehEspaco(char c);
int ehNumero(char c);
int ehLetra(char c);
int validaEmail(char *email);
int validoNoEmail(char c);
int validacao(char *aValidar, ClienteTipo tipo);

#endif // VALIDACAO_H
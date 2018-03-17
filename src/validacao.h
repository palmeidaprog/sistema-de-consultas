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
#include "medicos.h"
#include "clientes.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>


typedef enum Tipo {
    EMAIL,
    CPF,
    NOME,
    TELEFONE,
    CRM
} Tipo;

int pegaDado(char *dado, Tipo tipo);

int pegaTamanho(Tipo tipo);
void pegaErro(Tipo tipo, char *erro);
void pegaMensagem(Tipo tipo, char *msg);
int confirmacao(char *msg);

//--Validações----------------------------------------------------------------

int validaCRM(char *crm);
int validaCPF(char *cpf);
int restoCPF(int x); 
int validaNome(char *nome);
int validaTelefone(char *telefone);
int ehEspaco(char c);
int ehNumero(char c);
int ehLetra(char c);
int validaEmail(char *email);
int validoNoEmail(char c);
int validacao(char *aValidar, Tipo tipo);

#endif // VALIDACAO_H
/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#ifndef MEDICOS_TYPES_H
#define MEDICOS_TYPES_H

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

#include "tempo.h"

#define CRM_TAM 9 // 8 + 1
#define MEDICOS_ARQ "medicos.dat" 

#ifndef STRUCT_TAM
#define STRUCT_TAM

#define NOME_TAM 128
#define TELEFONE_TAM 17 // +1 para o /0
#define EMAIL_TAM 64

#endif // STRUCT_TAM

typedef enum Especialidade {
    CLINICA = 1, // clinico geral (tudo nao cirurgico)
    PEDIATRIA = 2, // crianças
    GERIATRIA = 3, // idosos
    ORTOPEDIA = 4, // musculos e ossos
    OFTAMOLOGIA = 5, // olhos
    NEUROLOGIA = 6, // sist. nervoso
    PSIQUIATRIA = 7, // mente
    UROLOGIA = 8, // sistema urinario e reprod. masculino
    GINECOLOGIA = 9, // sistema urinario e reprod. feminino
    OTORRONOLARINGOLOGIA = 10 // ouvido, nariz, garganta, pescoço
} Especialidade;

//tipo de medicos.h
typedef struct Medico {
    char crm[CRM_TAM];
    char nome[NOME_TAM];
    char telefone[TELEFONE_TAM];
    char email[EMAIL_TAM];
    Especialidade especialidade;
    int atendimento[5][2];
    int status;
} Medico;

// tipo de arvore_medicos.h (No da arvore)
typedef struct NoMedico {
    int indice;
    char crm[CRM_TAM];
    struct NoMedico *dir, *esq;
} NoMedico;


#endif // MEDICOS_TYPES_H#ifndef STRUCT_TAM

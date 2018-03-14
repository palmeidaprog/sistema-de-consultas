/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */


#ifndef MEDICOS_H
#define MEDICOS_H

// menu constantes
#define CADASTRAR_M 1
#define REMOVER_M 2
#define ALTERAR_M 3
#define PROCURA_CRM 4
#define PROCURA_NOME_M 5
#define EXIBIR_TODOS_M 6
#define VOLTAR_M 7

#include "medicos_types.h"
#include "arvore_medicos.h"
#include "io.h"
#include <stdio.h>

//--Menu----------------------------------------------------------------------

int menuMedicos();
void loopMedicos(FILE *arqMed, NoMedico **raizMedico);

#endif // MEDICOS_H

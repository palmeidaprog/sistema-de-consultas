/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "clientesconstantes.h"

int pegaTamanho(ClienteTipo tipo) {
    switch(tipo) {
        case EMAIL: 
            return 64;
        case CPF: 
            return 12;
        case NOME: 
            return 128;
        default:  // TELEFONE
            return 16;
    }
}

void pegaErro(ClienteTipo tipo, char *erro) {
    switch(tipo) {
        case EMAIL: 
            strcpy(erro, "ERRO: Email deve conter apenas uma arroba.\n");
            break;
        case CPF: 
            strcpy(erro, "ERRO: Apenas 11 numeros sem pontos e/ou hifen.\n");
            break;
        case NOME:
            strcpy(erro, "ERRO: Nome contem apenas letras e espacos.\n") ;
            break;
        default: // TELEFONE
            strcpy(erro, "ERRO: Numero de telefone apenas contem numeros.\n");
            break;
    }
}

void pegaMensagem(ClienteTipo tipo, char *msg) {
    switch(tipo) {
        case EMAIL: 
            strcpy(msg, "Insira o e-mail do cliente: ");
            break;
        case CPF: 
            strcpy(msg, "Insira o CPF (Sem pontos e hifen): ");
            break;
        case NOME:
            strcpy(msg, "Insira o nome do cliente: ");
            break;
        default:  // TELEFONE
            strcpy(msg, "Insira o telefone do cliente: ");
            break;
    }
}
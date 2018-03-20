/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "tempo.h"

void inicializarMatriz(Hora a[5][2]) {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 2; j++) {
            a[i][j].hora = -1;
            a[i][j].min = 0;
            a[i][j].seg = 0;
        }
    }
}

void imprimeTabelaHorario(Hora a[5][2]) {
    printf("|===========================================================|\n");
    printf("|   Tur   |   Seg   |   Ter   |   Qua   |   Qui   |   Sex   |\n");
    printf("|===========================================================|\n");
    printf("|  Manha  |");
    for(int i = 0; i < 5; i++) {
        printHora(a[i][0]);
    }
    printf("\n");
    printf("|  Tarde  |");
    for(int i = 0; i < 5; i++) {
        printHora(a[i][1]);
    }
    printf("\n");
    printf("|===================================================|\n");
}

// suporte para imprimeTabelaHorarrio
void printHora(Hora hora) {
    if(hora.hora == -1) {
        printf("    -    |");
    } else {
        printf("  %02dh%02d  |", hora.hora, hora.min);
    }
}

void preencherHorario(Hora a[5][2]) {
    char semana[5][25] = { "Segunda", "Terca", "Quarta", "Quinta", "Sexta" };
    char msg[100];

    for(int i = 0; i < 5; i++) {
        strcpy(msg, "Deseja incluir horario de atendimento na ");
        strcat(msg, semana[i]);
        strcat(msg, "?");
        if(confirmacao(msg)) {
            if(confirmacao("Expediente da manha?")) {
                a[i][0].hora = pegaInt(HORA);
                a[i][0].min = pegaInt(MIN);
            }
            if(confirmacao("Expediente da tarde?")) {
                a[i][1].hora = pegaInt(HORA);
                a[i][1].min = pegaInt(MIN);
            }
        }
    }
}



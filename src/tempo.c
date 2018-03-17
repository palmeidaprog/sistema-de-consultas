/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "tempo.h"

void imprimeTableHorario(Hora a[5][2]) {
    printf("|===========================================================|\n");
    printf("|   Tur   |   Seg   |   Ter   |   Qua   |   Qui   |   Sex   |\n");
    printf("|===========================================================|\n");
    printf("|  Manha  |");
    for(int i = 0; i < 5; i++) {
        printf("  %02dh%02d  |", a[i][0].hora, a[i][0].min);
    }
    printf("\n");
    printf("|  Tarde  |");
    for(int i = 0; i < 5; i++) {
        printf("  %02dh%02d  |", a[i][1].hora, a[i][1].min);
    }
    printf("\n");
    printf("|===================================================|\n");
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
                
            }
            if(confirmacao("Expediente da tarde?")) {

            }
        }
    }

}

Hora pegaHora() {
    Hora h;

    do {
        printf("Insira hora: ");
        scanf("%d", &h.hora);
        limpaBuffer();
    } while(h.hora < 1 || h.hora > 24);
        

}



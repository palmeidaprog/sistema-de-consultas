/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "tempo.h"

Data pegaData() { 
    Data data;

    size_t i = 0;
    n -= 2;
    
    while(i < n) {
        if(i == 2 || i == 4) {
            printf("/");
        }
        char = itoa(getche());
        if(str[i] == '\n') {
            // windows
            #if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  
            printf("\n"); 
            #endif
            break;
        }
        ++i;
    }
    str[i] = '\0';
    if(i == n) {
        printf("\n");
    }
}

int validaHora()

int validaData(Data data) {
    if()
}


/*void imprimeTabelaHorario(Hora a[5][2]) {
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
    printf("|===========================================================|\n");
    printf("\n");
}



/*void preencherHorario(Hora a[5][2]) {
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
}*/



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
    char str[DATA_TAM];
    int valido = 0;

    do {
        pegaDataTempo(str, DATA_TAM);
        
        if()
        else if(!validaData(data))

    } while(!valido)
}

int parseData(char *str, Data *data) {
    if()
}

// 0 = Domingo, 6 = sabado
int dayofweek(Data data) {
    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    data.ano -= data.mes < 3;
    return ( data.ano + data.ano/4 - data.ano/100 + data.ano/400 + 
        t[data.mes-1] + data.dia) % 7;
}


void pegaDataTempo(char *str, size_t n) {
    size_t i = 0;
    n -= 2;
    
    while(i < n) {
        formataStdin(n, i);
        char = getche();
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

// coloca no terminal as barras e dois pontos das hroas
void formataStdin(size_t n, size_t i) {
    if(n == DATA_TAM - 2) {
        if(i == 2 || i == 4) {
            printf("/");
        }
    } else if(n == HORA_TAM - 2) {
        if(i == 2) {
            printf(":");
        }
    }
}

int ultimoDiaMes(int mes) {
    if(mes == 2) {
        return 29;
    } else if(mes % 2 == 0 && mes <= 7) {
        return 30;
    } else if(mes % 2 != 0 && mes >= 8) {
        return 30;
    } else {
        return 31;
    }
}

int ehBissesto(int ano) {
    if(ano % 400 == 0) {
        return 1;
    } else if(ano % 4 == 0 && ano % 100 != 0) {
        return 1;
    }
    return 0;
}

int validaHora(Hora hora) {
    if(hora.hora < 0 || hora.hora > 23) {
        return 0;
    }
    if(hora.min < 0 || hora.min > 59) {
        return 0;
    }
    return 1;
}

int validaData(Data data) {
    if(data.mes < 1 || data.mes > 12) {
        return 0;
    } else if(data.mes == 2 && data.dia == 29 && !ehBissesto(data.ano)) {
        return 0;
    } else if(data.dia < 0 || data.dia > ultimoDiaMes(dia.mes)) {
        return 0;
    } else {
        return 1;
    }
}

// retorna < 0 se data for antes de hoje, 0 se for hoje e > 0 se for posterior
int comparaDatas(Data atual, Data data) {
    if(atual.ano == data.ano) {
        if(atual.mes == data.mes) {
            if(atual.dia == data.dia) {
                return 0;
            }
            return data.dia - atual.dia;
        }
        return data.mes - atual.mes;
    }
    return data.ano - atual.ano;
}
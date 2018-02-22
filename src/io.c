/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "io.h"

// limpa tela (usando comando nativo)
void limpaTela() {
    #if defined(Win32) || defined(_Win32) // windows
    system("cls");
    #else // POSIX
    system("clear");
    #endif
}

void pegaString(char *str, size_t n, char *msg) {
    size_t len;

    printf("%s", msg);
    fgets(str, n, stdin);
    len = strlen(str) - 1;
    if(str[len] == '\n') {
        str[len] = '\0';
    }
}

void limpaBuffer() {
    char c;

    do {
        scanf("%c", &c);
    } while(c != '\n');
}

// verifica a existencia do arquivo
int existeArquivo(char *nomeDoArquivo) {
    FILE *f;
    f = fopen(nomeDoArquivo, "rb");
    if(f == NULL) {
        return 0;
    }
    fclose(f);
    return 1;
}
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
    #if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
    system("cls");
    #else // POSIX
    system("clear");
    #endif
}

// nao é windows
#if !defined(Win32) && !defined(_Win32) && !defined(_WIN32) && !defined(_WIN64) 
int getche() {
      int c = 0;

      struct termios org_opts, new_opts;
      int res = 0;
      // Salva configuracao atual do terminal
      res = tcgetattr(STDIN_FILENO, &org_opts);
      assert(res == 0);
      // Novo parametro do terminal
      memcpy(&new_opts, &org_opts, sizeof(new_opts));
      new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT 
        | ECHOKE | ICRNL);
      tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
      c = getchar();
      // Restaura configs anteriormente salvas
      res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
      assert(res == 0);
      printf("%c", c);
      return(c);
}
#endif

void pegaCPF(char *str, size_t n) {
    size_t i = 0;
    n -= 2;
    
    while(i < n) {
        if(i == 3 || i == 6) {
            printf(".");
        } else if(i == 9) {
            printf("-");
        }
        str[i] = getche();
        if(str[i] == '\n') {
            break;
        }
        ++i;
    }
    str[i] = '\0';
    if(i == n) {
        printf("\n");
    }
}

void pegaString(char *str, size_t n) {
    size_t i = 0;
    n -= 2;
    
    while(i < n) {
        str[i] = getche();
        if(str[i] == '\n' || str[i] == 13) {
            #if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
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

/*void pegaString(char *str, size_t n) {
    size_t len;

    do {
        fgets(str, n, stdin);
    } while(strcmp(str, "\n") == 0); // rele a string caso so venha \n
    len = strlen(str) - 1;
    if(str[len] == '\n') {
        str[len] = '\0';
    }
}*/


void limpaBuffer() {
    char c;

    do {
        scanf("%c", &c);
    } while(c != '\n');
}

// verifica a existencia do arquivo
FILE *abreArquivo(char *nomeDoArquivo) {
    FILE *f;

    f = fopen(nomeDoArquivo, "r+b");
    if(f == NULL) {
        f = fopen(nomeDoArquivo, "wb");
        if(f == NULL) {
            printf("Nao foi possivel criar o arquivo %s\n", nomeDoArquivo);
        }
    }
    return f;
}

void fechaArquivo(FILE *f, char *nomeDoArquivo) {
    if(fclose(f) != 0) {
        printf("Nao foi possivel fechar o arquivo %s\n", nomeDoArquivo);
    }
}



/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#if defined(Win32) || defined(_Win32) || defined(_WIN32) || defined(_WIN64)  // windows
#pragma warning(disable: 4996)
#endif

#include "io.h"
#include "validacao.h"
#include "clientes.h"
#include "medicos.h"
#include <stdio.h>

//--Protótipos----------------------------------------------------------------

void sobre();
int menuPrincipal();
// mover para os modulos posteriormente
void loopMedicos();
void loopConsultas();

//--main()--------------------------------------------------------------------

int main() {
    NoCliente *raizCliente = NULL;
    NoMedico *raizMedico = NULL;
    FILE *arqCliente, *arqMedico;
    int m;

    arqCliente = abreArquivo(CLIENTE_ARQ);
    arqMedico = abreArquivo(MEDICOS_ARQ);
    criaArvoreCliente(arqCliente, &raizCliente);
    criaArvoreMedico(arqMedico, &raizMedico);
    limpaTela();
    sobre();

    do {
        m = menuPrincipal();
        switch(m) {
            case 1:
                limpaTela();
                loopClientes(arqCliente, &raizCliente);
                break;
            case 2:
                limpaTela(); 
                loopMedicos(arqMedico, &raizMedico);
                break;
            case 3: 
                limpaTela();
                loopConsultas();
                break;
            case 4:
                limpaArquivoCliente(arqCliente);
                break;
            default:
                limpaTela();
                printf("Opcao invalida!\n");
                break;
        }

    } while(m != 4);

    return 0;
}

//--Implementaçòes------------------------------------------------------------

void sobre() {
    printf("SISTEMA DE MARCACAO DE CONSULTAS\n");
    printf("PROJETO 01 - PRATICA DE PROGRAMACAO\n");
    printf("Prof. Me. Ana Eliza Moura\n");
    printf("Paulo R. Almeida Filho <pauloalmeidaf@gmail.com>\n\n");
}

int menuPrincipal() {
    int resp;

    printf("|==========================|\n");
    printf("|      Menu Principal      |\n");
    printf("|                          |\n");
    printf("|  1 - Clientes            |\n");
    printf("|  2 - Medicos             |\n");
    printf("|  3 - Consultas           |\n");
    printf("|  4 - Sair                |\n");
    printf("|                          |\n");
    printf("|==========================|\n\n");
    printf("Sua escolha: ");
    scanf("%d", &resp);
    limpaBuffer();

    return resp;
}

void loopConsultas() { }
/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "medicos.h"

void cadastrarMedico(FILE *arq, NoMedico **raizMedico, char *crm) {
    NoMedico *no;
    Medico *med;
    
    if(buscar(*raizMedico, crm) != NULL) {
        printf("Medico ja cadastrado\n\n");
        return ;
    }
    
    med = criaMedico(crm);
    no = escreveMedico(arq, med, -1);
    if(!no) {
        printf("ERRO: Nao foi possivel gravar no arquivo \"%s\"", 
            MEDICOS_ARQ);
        return ;
    }
    inserirIndiceMedico(raizMedico, no);
    printf("Medico %s foi cadastrado com sucesso\n\n", crm);
}

//--Menu----------------------------------------------------------------------

int menuMedicos() {
    int resp;

    printf("|=================================|\n");
    printf("|       Menu Medicos              |\n");
    printf("|                                 |\n");
    printf("|  %d - Cadastrar                  |\n", CADASTRAR_M);
    printf("|  %d - Remover                    |\n", REMOVER_M);
    printf("|  %d - Alterar                    |\n", ALTERAR_M);
    printf("|  %d - Procurar por crm           |\n", PROCURA_CRM);
    printf("|  %d - Procurar por Nome          |\n", PROCURA_NOME_M);
    printf("|  %d - Imprime Todos Medicos      |\n", EXIBIR_TODOS_M);
    printf("|  %d - Voltar                     |\n", VOLTAR_M);
    printf("|                                 |\n");
    printf("|=================================|\n\n");
    printf("Sua escolha: ");
    scanf("%d", &resp);
    limpaBuffer();

    return resp;
}

void loopMedicos(FILE *arqMed, NoMedico **raizMedico) {
    int m;
    char crm[CRM_TAM], nome[NOME_TAM];

    do {
        m = menuMedicos();
        switch(m) {
            case CADASTRAR_M:
                limpaTela();
                if(pegaDadoMedico(crm, crm)) {
                    cadastrarMedico(arqMed, raizMedico, crm);
                }
                break;
            case REMOVER_M:
                limpaTela();
                if(pegaDadoMedico(crm, crm)) {
                    removerMedico(arqMed, raizMedico, crm);
                }
                break;
            case ALTERAR_M:
                limpaTela();
                if(pegaDadoMedico(crm, crm)) {
                    alterarMedico(arqMed, raizMedico, crm);
                }
                break;
            case PROCURA_CRM:
                limpaTela();
                if(pegaDadoMedico(crm, crm)) {
                    buscacrm(arqMed, *raizMedico, crm);
                }
                break;
            case PROCURA_NOME_M:
                limpaTela();
                if(pegaDadoMedico(nome, NOME)) {
                    buscaNome(arqMed, nome);
                }
                break;
            case EXIBIR_TODOS_M: 
                limpaTela();
                exibirTodos(arqMed, *raizMedico);
                break;
            case VOLTAR_M:
                limpaTela();
                break;  
            default: 
                limpaTela();
                printf("Opcao invalida!\n");
                break;
        }
    } while(m != VOLTAR_M);
}
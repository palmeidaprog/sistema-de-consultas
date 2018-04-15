/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "consultas.h"

void marcarConsulta(Cliente *paciente, Medico *medico) { // TODO: parametros
    Consulta consulta;

    printf("Marcar Consulta:\n");
    strcpy(consulta.clienteCpf, paciente->cpf);
    strcpy(consulta.medicoCrm, medico->crm);

    do {
        imprimeMedico(medico, 0);
        consulta.codigo = novoCodConsulta();
        if(consulta.codigo == -1) {
            printf("Impossivel criar consulta (erro nos codigos)\n\n");
            return;
        }
        consulta.data = pegaData();
        // consulta a maatriuz de atendimento do medico e ve se ele trabalha
        // naquele dia da semana/turno.
        if((medico->atendimento[consulta.turno][consulta.data.diaDaSemana 
                - 1])) {
            if(medicoCheio()) { // TODO: Verificar se o medico esta cheio
                printf("\nO medico %s (CRM: %s) encontra-se com o turno da data ",
                        medico->nome, medico->crm);
                printf("%s cheio.\n ", consulta.data.toString);
                if(confirmacao("Entrar na fila de espera? (N para escolher nova data) "
                            )) {
                    // TODO: terminar logica do enfileiramento
                    printf("Consulta na fila de espera.\n\n");
                    return ;
                } else {
                    printf("Consulta marcaado com sucesso.\n\n");
                    return ;
                }
            } else {
                printf("Medico nao atende nesse dia.");
            }
        } 
    } while(confirmacao("Deseja tentar a consulta em outra Data/Turno?"));

    printf("Nenhuma consulta foi agendada.\n\n");
    
}

// suporte para marcaConsulta()'no loopConsultas()
int pegaPaciente(FILE *arqCliente, NoCliente *raizCliente, Cliente *cliente) {
    char cpf[CPF_TAM];

     do {
        if(pegaDado(cpf, CPF)) {
            if(validaProcuraCliente(buscarCliente(arqCliente, raizCliente, 
                cpf, cliente))) {
                return 1;
            }
        }
    } while(confirmacao("Deseja tentar outro CPF?"));
    return 0;
}

// suporte para marcaConsulta()'no loopConsultas()
int pegaMedico(FILE *arqMedico, NoMedico *raizMedico, Medico *medico) {
    char crm[CRM_TAM];

    do {
        if(pegaDado(crm, CRM)) {
            if(validaProcuraMedico(buscaMedico(arqMedico, raizMedico, crm, 
                medico))) { 
                return 1;
            }
        }
    } while(confirmacao("Deseja tentar outro CRM?"));
    return 0;
}

//--Arquivo-------------------------------------------------------------------

// pega um novo codigo
int novoCodConsulta() {
    FILE *f;
    int cod = 0;
    char nomeDoArquivo[] = "codigo.dat";

    f = fopen(nomeDoArquivo, "r+b");
    fseek(f, 0, SEEK_SET);
    if(f == NULL) {
        f = fopen(nomeDoArquivo, "w+b");
        if(f == NULL) {
            printf("Nao foi possivel criar o arquivo %s\n\n", nomeDoArquivo);
            return -1;
        } else if(fwrite(&cod, sizeof(int), 1, f) != 1) {
            printf("Erro ao inicializar sistema de codigo.\n\n");
            return -1;
        }
        
    }
    if(fread(&cod, sizeof(int), 1, f) != 1) {
        printf("Erro ao ler arquivo de codigos.\n\n");
        return -1;
    }
    ++cod;
    if(fwrite(&cod, sizeof(int), 1, f) != 1) {
        printf("Erro ao escrever arquivo de codigos.\n\n");
        return -1;
    }

    return cod;
 }

//--Menu----------------------------------------------------------------------

int menuMedicos() {
    int resp;

    printf("|=================================|\n");
    printf("|       Menu Medicos              |\n");
    printf("|                                 |\n");
    printf("|  %d - Marcar                     |\n", MARCAR_C);
    printf("|  %d - Consultar Pacientes        |\n", PACIENTES_C);
    printf("|  %d - Consultar consultas        |\n", CONSULTAS_C);
    printf("|  %d - Desmarcar Consultas        |\n", DESMARCAR_C);
    printf("|  %d - Voltar                     |\n", VOLTAR_C);
    printf("|                                 |\n");
    printf("|=================================|\n\n");
    printf("Sua escolha: ");
    scanf("%d", &resp);
    limpaBuffer();

    return resp;
}

void loopConsultas(FILE *arqCliente, FILE *arqMed, NoCliente **raizCliente, 
            NoMedico **raizMedico) {
    int m, n;
    Cliente paciente;
    Medico medico;
    char crm[CRM_TAM], cpf[CPF_TAM];
    // TODO: ajeitar menus e chamadas
    do {
        m = menuMedicos();
        switch(m) {
            case MARCAR_C:
                limpaTela();
                if(pegaPaciente(arqCliente, *raizCliente, &paciente) && 
                    pegaMedico(arqMed, *raizMedico, &medico)) {
                    marcarConsulta(&paciente, &medico);
                }
                break;
            case REMOVER_M:
                if(pegaDado(crm, CRM)) {
                    removerMedico(arqMed, raizMedico, crm);
                }
                break;
            case ALTERAR_M:
                if(pegaDado(crm, CRM)) {
                    alterarMedico(arqMed, raizMedico, crm);
                }
                break;
            case PROCURA_CRM:
                if(pegaDado(crm, CRM)) {
                    buscaCRM(arqMed, *raizMedico, crm);
                }
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
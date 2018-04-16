/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "consultas.h"

void marcarConsulta(FILE *arq, NoConsulta **raiz, Cliente *paciente, Medico 
        *medico, int *codigo) { 
    Consulta consulta;

    printf("Marcar Consulta:\n");
    strcpy(consulta.clienteCpf, paciente->cpf);
    strcpy(consulta.medicoCrm, medico->crm);

    do {
        imprimeMedico(medico, 0);
        consulta.data = pegaData();
        // consulta a maatriuz de atendimento do medico e ve se ele trabalha
        // naquele dia da semana/turno.
        if((medico->atendimento[consulta.turno][consulta.data.diaDaSemana 
                - 1])) {
            if(medicoCheio(*raiz, consulta.data, consulta.medicoCrm)) { 
                printf("\nO medico %s (CRM: %s) encontra-se com o turno da data ",
                        medico->nome, medico->crm);
                printf("%s cheio.\n ", consulta.data.toString);
                if(confirmacao("Entrar na fila de espera? (N para escolher nova data) "
                            )) {
                    insereConsulta(arq, raiz, &consulta, codigo, 
                    "Consulta na fila de espera.\n\n");
                    return;
                }
            } else { // caso tenha 10 pacientes para o medico
                insereConsulta(arq, raiz, &consulta, codigo, 
                    "Consulta marcada com sucesso.\n\n");
                return ;
            }
        } else { // medico nao tem atendimento nesse dia
            printf("Medico nao atende nesse dia.");
        }
    } while(confirmacao("Deseja tentar a consulta em outra Data/Turno?"));
    printf("Nenhuma consulta foi agendada.\n\n");
}

// suporte para marcaConsulta()
void insereConsulta(FILE *arq, NoConsulta **raiz, Consulta *consulta, int 
            *codigo, char *msg) {
    NoConsulta *no;
    
    no = escreveConsulta(arq, consulta, -1, codigo);
    if(no == NULL) {
        printf("Erro na escrita do arquivo de Consultas %s\n",
                CONSULTAS_ARQ);
    }
    inserirIndiceConsulta(raiz, no);
    printf("%s", msg);
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

 // retorna 1 se conseguiu incluir no arquivo
NoConsulta *escreveConsulta(FILE *arq, Consulta *c, int pos, int *codigo) {
    NoConsulta *retorno = NULL;

    if(pos == -1) {
        fseek(arq, 0, SEEK_END);
    }
    else {
        fseek(arq, pos, SEEK_SET);
    }
    if(fwrite(c, sizeof(Consulta), 1, arq) && ftell(arq) == 1){
        retorno = criaNoConsulta(c, (ftell(arq) - sizeof(Consulta)) /
             sizeof(Consulta), codigo);
        fflush(arq); // força os dados a serem escritos
    }
    return retorno;
}

// retorna 0 se nao conseguir ler
int leConsulta(FILE *arq, long int pos, Consulta *cliente) {

    fseek(arq, pos, SEEK_SET);
    if(fread(cliente, sizeof(Consulta), 1, arq) != 1) {
        return 0;
    }
    return 1;
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

void loopConsultas(FILE *arqConsulta, FILE *arqCliente, FILE *arqMed, 
            NoConsulta **raizConsulta, NoCliente **raizCliente, NoMedico 
            **raizMedico, int *codigo) {
    int m;
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
                    marcarConsulta(arqConsulta, raizConsulta, &paciente, 
                            &medico, codigo);
                }
                break;
            case REMOVER_M:
                
                break;
            case ALTERAR_M:
                
                break;
            case PROCURA_CRM:
                
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
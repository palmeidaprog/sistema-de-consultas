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
    consulta.status = ATIVO;

    //TODO: validaacao para impedir mais de uma consulta por cliente
    do {
        imprimeMedico(medico, 0);
        consulta.data = pegaData();
        // consulta a maatriuz de atendimento do medico e ve se ele trabalha
        // naquele dia da semana/turno.
        if((medico->atendimento[consulta.data.turno][consulta.data.diaDaSemana 
                - 1])) {
            if(medicoCheio(*raiz, consulta.data, consulta.medicoCrm)) { 
                printf("\nO medico %s (CRM: %s) encontra-se com o turno da data ",
                        medico->nome, medico->crm);
                printf("%s cheio.\n\n", consulta.data.toString);
                if(confirmacao("Entrar na fila de espera? (N para escolher nova data) "
                            )) {
                    consulta.status = ESPERA;
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
            printf("Medico nao atende nesse dia.\n\n");
        }
    } while(confirmacao("Deseja tentar a consulta em outra Data/Turno?"));
    printf("Nenhuma consulta foi agendada.\n\n");
}


void consultaMedico(FILE *arq, NoConsulta *raiz, Medico *medico) {
    Data data;

    data = pegaData();
    imprimeMedico(medico, 0);
    if(!buscaConsultaCRM(arq, raiz, data, medico->crm)) {
        printf("Nao ha pacientes para o turno.\n\n");
    }
}

void consultaPaciente(FILE *arq, NoConsulta *raiz, Medico *medico, Data 
            data) {
    
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

int buscaConsultaCRM(FILE *arq, NoConsulta *raiz, Data data, char *crm) {
    int cont = 0;
    Consulta c;
    
    while(raiz != NULL) {
        if(comparaDatas(raiz->data, data) == 0 && strcmp(raiz->medicoCrm, crm)
                == 0) {
            if(!cont) {
               printf("Clientes Agendados para o turno:\n\n");
            }
            if(cont == 10){
                if(confirmacao("Deseja imprimir lista de espera?")){
                    printf("Em espera de Cancelamentos:\n\n");
                } else {
                    break;
                }
            }
            ++cont;
            if(!leConsulta(arq, raiz->indice * sizeof(Consulta), &c)) {
                printf("Erro ao ler o arquivo de consulta!\n\n");
                return 0;
            }
            imprimeConsulta(c, cont);
        } 
        if(comparaDatas(data, raiz->data) < 0) {
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }
    return cont;
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
int leConsulta(FILE *arq, long int pos, Consulta *consulta) {

    fseek(arq, pos, SEEK_SET);
    if(fread(consulta, sizeof(Consulta), 1, arq) != 1) {
        return 0;
    }
    return 1;
}

//--io------------------------------------------------------------------------

void imprimeConsulta(Consulta c, int pos) {
    char formatado[CPF_FORMAT];

    if(pos != 0) {
        printf("Consulta No. %d:\n", pos);
    }
    printf("Data: %s\n", c.data.toString);
    formataCPF(formatado, c.clienteCpf);
    printf("CPF do Cliente: %s\n", formatado);
    printf("STATUS: ");
    switch(c.status) {
        case ATIVO: 
            printf("ATIVO\n");
            break;
        default:  // espera
            printf("EM ESPERA\n");
    }
    printf("\n");
}




//--Menu----------------------------------------------------------------------

int menuConsultas() {
    int resp;

    printf("|=================================|\n");
    printf("|       Menu Medicos              |\n");
    printf("|                                 |\n");
    printf("|  %d - Marcar                     |\n", MARCAR_C);
    printf("|  %d - Consultar consultas        |\n", CONSULTAS_C);
    printf("|  %d - Consultar Pacientes        |\n", PACIENTES_C);
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
    //char crm[CRM_TAM], cpf[CPF_TAM];
    // TODO: ajeitar menus e chamadas
    do {
        m = menuConsultas();
        switch(m) {
            case MARCAR_C:
                limpaTela();
                if(pegaPaciente(arqCliente, *raizCliente, &paciente) && 
                    pegaMedico(arqMed, *raizMedico, &medico)) {
                    marcarConsulta(arqConsulta, raizConsulta, &paciente, 
                            &medico, codigo);
                }
                break;
            case CONSULTAS_C:
                limpaTela();
                if(pegaMedico(arqMed, *raizMedico, &medico)) {
                    consultaMedico(arqConsulta, *raizConsulta, &medico);
                }
                break;
            case ALTERAR_M:
                 
                break;
            case PROCURA_CRM:
                
                break;
            case VOLTAR_C:
                limpaTela();
                break;  
            default: 
                limpaTela();
                printf("Opcao invalida!\n");
                break;
        }
    } while(m != VOLTAR_C);
}
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
    
    if(buscarMedico(*raizMedico, crm) != NULL) {
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

void exibirTodosMedicos(FILE *arq, NoMedico *raiz, int *pos) {
    Medico medico;

    if(raiz == NULL) {
        printf("Não existe medicos cadastrados\n\n");
        return ;
    }

    if(raiz->esq != NULL) {
        exibirTodosMedicos(arq, raiz->esq, pos);
    }
    if(!leMedico(arq, raiz->indice * sizeof(Medico), &medico)) {
        printf("Erro ao ler o arquivo de Medicos (medicos.dat)");
    }
    imprimeMedico(&medico, ++*pos);
    if(raiz->dir != NULL) {
        exibirTodosMedicos(arq, raiz->dir, pos);
    }
}

void removerMedico(FILE *arq, NoMedico **raiz, char *crm) {
    Medico medico;
    NoMedico *pos;

    pos = buscarMedico(*raiz, crm);
    if(pos == NULL) {
        printf("Medico com esse CRM (%s) nao existe\n\n", crm);
        return ;
    }

    if(!leMedico(arq, pos->indice * sizeof(Medico), &medico)) {
        printf("Erro ao ler o arquivo %s\n\n", MEDICOS_ARQ);
    }
    medico.status = 0;
    escreveMedico(arq, &medico, pos->indice * sizeof(Medico));
    removerIndiceMedico(raiz, pos);
    printf("Medico %s removido com sucesso\n\n", crm);
}

Medico *criaMedico(char *crm) { 
    Medico *med = (Medico *) malloc(sizeof(Medico));

    strcpy(med->crm, crm);
    pegaDado(med->nome, NOME);
    pegaDado(med->telefone, TELEFONE);
    pegaDado(med->email, EMAIL);
    preencherHorario(med->atendimento);
    med->especialidade = menuEspecialidades();
    med->status = 1;

    return med;
}

void alterarMedico(FILE *arq, NoMedico **raiz, char *crm) {
    NoMedico *pos;
    Medico medico;

    pos = buscarMedico(*raiz, crm);
    if(pos == NULL) {
        printf("Medico nao existe\n\n");
        return ;
    }

    if(!leMedico(arq, pos->indice * sizeof(Medico), &medico)) {
        printf("Erro ao ler arquivo %s\n\n", MEDICOS_ARQ);
    }
    imprimeMedico(&medico, 0);
    printf("Digite os novos dados:\n\n");
    if(confirmacao("Deseja alterar o nome?")) {
        pegaDado(medico.nome, NOME);
    }

    if(confirmacao("Deseja alterar o telefone?")) {
        pegaDado(medico.telefone, TELEFONE);
    }

    if(confirmacao("Deseja alterar o e-mail?")) {
        pegaDado(medico.email, EMAIL);
    }

    if(confirmacao("Deseja alterar a especialidade?")) {
        medico.especialidade = menuEspecialidades();
    }

    if(confirmacao("Deseja alterar o horario de atendimento?")) {
        preencherHorario(medico.atendimento);
    }
    
    escreveMedico(arq, &medico, pos->indice * sizeof(Medico));
    printf("Dados modificados com exito\n\n");
}

void buscaNomeMedico(FILE *arq, char *nome) {
    int pos;
    Medico medico;

    pos = buscaPorNomeMedico(arq, nome);
    if(pos == -1) {
        printf("Medico com nome %s nao existe\n\n", nome);
    } else {
        if(!leMedico(arq, pos, &medico)) {
            printf("Erro ao ler medico do arquivo\n\n");
        } else {
            imprimeMedico(&medico, 0);
        }
    }
}

//--Arquivo-------------------------------------------------------------------

void listaEspecialidade(FILE *arq, Especialidade e) {
    int const TAM = 100;
    int n, pos = 0;
    char especNome[20];
    Medico medicos[100];

    pegaEspecialidade(e, especNome);
    printf("Medicos da Especialidade %s:\n\n", especNome);
    fseek(arq, 0, SEEK_SET);
    do {
        n = fread(medicos, sizeof(Medico), TAM, arq);
        for(int i = 0; i < n; ++i) {
            if(medicos[i].status && medicos[i].especialidade == e) {
                ++pos;
                imprimeMedico(&medicos[i], pos);
            }
        }
    } while(n == TAM);
    if(!feof(arq)) {
        printf("Erro ao ler o arquivo de Medicos!\n\n");
    } else {
        printf("Existem um total de %d medicos especialistas em %s.\n\n", pos, 
            especNome);
    }
}

int buscaPorNomeMedico(FILE *arq, char *nome) {
    int const TAM = 100;
    int n;
    Medico medicos[TAM];

    fseek(arq, 0, SEEK_SET);
    do {
        n = fread(medicos, sizeof(Medico), TAM, arq);
        for(int i = 0; i < n; ++i) {
            if(strcmp(nome, medicos[i].nome) == 0) {
                return ftell(arq) - (sizeof(Medico) - (sizeof(Medico) * 
                    (n - (i+1))));
            }
        }
    } while(n == TAM);
    return -1;    
}

// retorna 1 se conseguiu incluir no arquivo
NoMedico *escreveMedico(FILE *arq, Medico *med, int pos) {
    NoMedico *retorno = NULL;

    if(pos == -1) {
        fseek(arq, 0, SEEK_END);
    }
    else {
        fseek(arq, pos, SEEK_SET);
    }
    if(fwrite(med, sizeof(Medico), 1, arq) && ftell(arq) != -1){
        retorno = criaNoMedico(med, (ftell(arq) - sizeof(Medico)) /
             sizeof(Medico));
        fflush(arq); // força os dados a serem escritos
    }
    return retorno;
}

// retorna 0 se nao conseguir ler
int leMedico(FILE *arq, long long pos, Medico *medico) {

    fseek(arq, pos, SEEK_SET);
    if(fread(medico, sizeof(Medico), 1, arq) != 1) {
        return 0;
    }
    return 1;
}

void limpaArquivoMedico(FILE *arq) {
    FILE *aux;
    int const TAM = 25;
    int nLidos = 0, nEscrever = 0;
    Medico lidos[TAM], escrever[TAM];

    aux = abreArquivo("aux.dat");
    fseek(arq, 0, SEEK_SET);
    do {
        nLidos = fread(lidos, sizeof(Medico), TAM, arq);
        nEscrever = 0;
        for(int i = 0; i < nLidos; i++) {
            if(lidos[i].status) {
                escrever[nEscrever++] = lidos[i];
            }
        }

        if(nEscrever != fwrite(escrever, sizeof(Medico), nEscrever, aux)) {
            printf("Erro ao executar limpeza no arquivo %s\n\n", MEDICOS_ARQ);
        }
    } while(nLidos == TAM);

    fflush(aux);
    fechaArquivo(arq, MEDICOS_ARQ);
    fechaArquivo(aux, "aux.dat");
    remove(MEDICOS_ARQ);
    rename("aux.dat", MEDICOS_ARQ);
}

//--io------------------------------------------------------------------------

void imprimeMedico(Medico *med, int pos) {
    char especNome[20];

    if(pos) { // so imprime se pos != 0
        printf("Medico No. %d\n", pos);
    }
    printf("Nome: %s\n", med->nome);
    printf("CRM: %s\n", med->crm);
    printf("Telefone: %s\n", med->telefone);
    printf("E-mail: %s\n", med->email);
    pegaEspecialidade(med->especialidade, especNome);
    printf("Especialidade: %s\n", especNome);
    imprimeTabelaHorario(med->atendimento);
    printf("\n");
}

void imprimeTabelaHorario(int a[][2]) {
    printf("|===================================|\n");
    printf("|Turno| Seg | Ter | Qua | Qui | Sex |\n");
    printf("|===================================|\n");
    printf("|Manha|");
    for(int i = 0; i < 5; i++) {
        printHora(a[i][0]);
    }
    printf("\n");
    printf("|Tarde|");
    for(int i = 0; i < 5; i++) {
        printHora(a[i][1]);
    }
    printf("\n");
    printf("|===================================|\n");
    printf("\n");
}

// suporte para imprimeTabelaHorarrio
void printHora(int x) {
    if(!x) {
        printf("     |");
    } else {
        printf("  X  |");
    }
}

void preencherHorario(int a[][2]) {
    char semana[5][25] = { "Segunda", "Terca", "Quarta", "Quinta", "Sexta" };
    char msg[100];

    for(int i = 0; i < 5; i++) {
        strcpy(msg, "Deseja incluir horario de atendimento na ");
        strcat(msg, semana[i]);
        strcat(msg, "?");
        if(confirmacao(msg)) {
            a[i][0] = confirmacao("Expediente da manha?");
            a[i][1] = confirmacao("Expediente da tarde?");
        } else {
            a[i][0] = 0;
            a[i][1] = 0;
        }
    }
}

void pegaEspecialidade(Especialidade e, char *especNome) {
    switch(e) {
        case 1:
            strcpy(especNome, "Clinica");
            break;
        case 2:
            strcpy(especNome, "Pediatria");
            break;
        case 3:
            strcpy(especNome, "Geriatria");
            break;
        case 4:
            strcpy(especNome, "Ortopedia");
            break;
        case 5:
            strcpy(especNome, "Oftamologia");
            break;
        case 6:
            strcpy(especNome, "Neurologia");
            break;
        case 7:
            strcpy(especNome, "Psiquiatria");
            break;
        case 8:
            strcpy(especNome, "Urologia");
            break;
        case 9:
            strcpy(especNome, "Ginecologia");
            break;
        default:
            strcpy(especNome, "Otorrinolaringologia");
            break;
            
    }

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
    printf("|  %d - Medicos da Especialidade   |\n", MEDICOS_ESPEC_M);
    printf("|  %d - Imprime Todos Medicos      |\n", EXIBIR_TODOS_M);
    printf("|  %d - Voltar                     |\n", VOLTAR_M);
    printf("|                                 |\n");
    printf("|=================================|\n\n");
    printf("Sua escolha: ");
    scanf("%d", &resp);
    limpaBuffer();

    return resp;
}



int menuEspecialidades() {
    int resp, erro = 0;

    do {
        if(erro) {
            limpaTela();
            printf("Especialidade invalida.\n");
        }
        printf("|=================================|\n");
        printf("|     Escolha a Especialidade     |\n");
        printf("|                                 |\n");
        printf("|  %d - CLINICA                    |\n", CLINICA);
        printf("|  %d - PEDIATRIA                  |\n", PEDIATRIA);
        printf("|  %d - GERIATRIA                  |\n", GERIATRIA);
        printf("|  %d - ORTOPEDIA                  |\n", ORTOPEDIA);
        printf("|  %d - OFTAMOLOGIA                |\n", OFTAMOLOGIA);
        printf("|  %d - NEUROLOGIA                 |\n", NEUROLOGIA);
        printf("|  %d - PSIQUIATRIA                |\n", PSIQUIATRIA);
        printf("|  %d - UROLOGIA                   |\n", UROLOGIA);
        printf("|  %d - GINECOLOGIA                |\n", GINECOLOGIA);
        printf("|  %d - OTORRONOLARINGOLOGIA       |\n", OTORRONOLARINGOLOGIA);
        printf("|                                 |\n");
        printf("|=================================|\n\n");
        printf("Sua escolha: ");
        scanf("%d", &resp);
        limpaBuffer();
        erro = 1;
    } while(resp < CLINICA || resp > OTORRONOLARINGOLOGIA);
    return resp;

}

void loopMedicos(FILE *arqMed, NoMedico **raizMedico) {
    int m, n;
    char crm[CRM_TAM], nome[NOME_TAM];

    do {
        m = menuMedicos();
        switch(m) {
            case CADASTRAR_M:
                limpaTela();
                if(pegaDado(crm, CRM)) {
                    cadastrarMedico(arqMed, raizMedico, crm);
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
                limpaTela();
                if(pegaDado(crm, CRM)) {
                    //buscaCRM(arqMed, *raizMedico, crm);
                }
                break;
            case PROCURA_NOME_M:
                limpaTela();
                if(pegaDado(nome, NOME)) {
                    buscaNomeMedico(arqMed, nome);
                }
                break;
            case EXIBIR_TODOS_M: 
                limpaTela();
                n = 0;
                exibirTodosMedicos(arqMed, *raizMedico, &n);
                break;
            case MEDICOS_ESPEC_M: 
                limpaTela();
                listaEspecialidade(arqMed, menuEspecialidades());
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
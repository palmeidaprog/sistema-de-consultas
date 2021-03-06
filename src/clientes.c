/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "clientes.h"

void cadastrarCliente(FILE *arq, NoCliente **raizCliente, char *cpf) {
    NoCliente *no;
    Cliente *cl;
    char formatado[CPF_FORMAT];
    
    if(buscar(*raizCliente, cpf) != NULL) {
        printf("Cliente ja cadastrado\n\n");
        return ;
    }
    
    cl = criaCliente(cpf);
    no = escreveCliente(arq, cl, -1);
    if(!no) {
        printf("ERRO: Nao foi possivel gravar no arquivo \"%s\"", 
            CLIENTE_ARQ);
        return ;
    }
    inserirIndiceCliente(raizCliente, no);
    formataCPF(formatado, cpf);
    printf("Cliente %s foi cadastrado com sucesso\n\n", formatado);
}

void exibirTodos(FILE *arq, NoCliente *raiz, int *pos) {
    Cliente cliente;
    
    if(raiz == NULL) {
        printf("Não existe clientes cadastrados\n\n");
        return ;
    }

    if(raiz->esq != NULL) {
        exibirTodos(arq, raiz->esq, pos);
    }
    leCliente(arq, raiz->indice * sizeof(Cliente), &cliente);
    imprimeCliente(&cliente, ++*pos);
    if(raiz->dir != NULL) {
        exibirTodos(arq, raiz->dir, pos);
    }

}

void removerCliente(FILE *arq, NoCliente **raiz, char *cpf) {
    Cliente cliente;
    NoCliente *pos;

    pos = buscar(*raiz, cpf);
    if(pos == NULL) {
        printf("Cliente com esse CPF (%s) nao existe\n\n", cpf);
        return ;
    }

    if(!leCliente(arq, pos->indice * sizeof(Cliente), &cliente)) {
        printf("Erro ao ler o arquivo %s\n\n", CLIENTE_ARQ);
    }
    cliente.status = 0;
    escreveCliente(arq, &cliente, pos->indice * sizeof(Cliente));
    removerIndiceCliente(raiz, pos);
    printf("Cliente %s removido com sucesso\n\n", cpf);
}

Cliente *criaCliente(char *cpf) {
    Cliente *cl = (Cliente *) malloc(sizeof(Cliente));

    strcpy(cl->cpf, cpf);
    pegaDado(cl->nome, NOME);
    pegaDado(cl->telefone, TELEFONE);
    pegaDado(cl->email, EMAIL);
    cl->status = 1;

    return cl;
}

void alterarCliente(FILE *arq, NoCliente **raiz, char *cpf) {
    NoCliente *pos;
    Cliente cliente;

    pos = buscar(*raiz, cpf);
    if(pos == NULL) {
        printf("Cliente nao existe\n\n");
        return ;
    }

    if(!leCliente(arq, pos->indice * sizeof(Cliente), &cliente)) {
        printf("Erro ao ler arquivo %s\n\n", CLIENTE_ARQ);
    }
    imprimeCliente(&cliente, 0);
    printf("Digite os novos dados:\n\n");
    if(confirmacao("Deseja alterar o nome?")) {
        pegaDado(cliente.nome, NOME);
    }
    if(confirmacao("Deseja alterar o telefone?")) {
        pegaDado(cliente.telefone, TELEFONE);
    }
    if(confirmacao("Deseja alterar o e-mail?")) {
        pegaDado(cliente.email, EMAIL);
    }

    escreveCliente(arq, &cliente, pos->indice * sizeof(Cliente));
    printf("Dados modificados com exito\n\n");
}

void buscaNome(FILE *arq, char *nome) {
    int pos;
    Cliente cliente;

    pos = buscaPorNome(arq, nome);
    if(pos == -1) {
        printf("Cliente com nome %s nao existe\n\n", nome);
    } else {
        if(!leCliente(arq, pos, &cliente)) {
            printf("Erro ao ler cliente do arquivo\n\n");
        } else {
            imprimeCliente(&cliente, 0);
        }
    }
}

void buscaCPF(FILE *arq, NoCliente *raiz, char *cpf) {
    Cliente cliente;

    if(validaProcuraCliente(buscarCliente(arq, raiz, cpf, &cliente))) {
        imprimeCliente(&cliente, 0);
    }
}

// retorna 0 se nao conseguir achar (para consultas)
int buscarCliente(FILE *arq, NoCliente *raiz, char *cpf, Cliente *cliente) {
    NoCliente *pos;

    pos = buscar(raiz, cpf);
    if(pos == NULL) {
        return -1;
    } else {
        if(!leCliente(arq, pos->indice * sizeof(Cliente), cliente)) {
            return 0;
        }
    }
    return 1;
}

//--Arquivo-------------------------------------------------------------------

int buscaPorNome(FILE *arq, char *nome) {
    int const TAM = 100;
    int n;
    Cliente clientes[100];

    fseek(arq, 0, SEEK_SET);
    do {
        n = fread(clientes, sizeof(Cliente), TAM, arq);
        for(int i = 0; i < n; ++i) {
            if(strcmp(nome, clientes[i].nome) == 0) {
                return ftell(arq) - (sizeof(Cliente) - (sizeof(Cliente) * 
                    (n - (i+1))));
            }
        }
    } while(n == TAM);
    return -1;    
}

// retorna 1 se conseguiu incluir no arquivo
NoCliente *escreveCliente(FILE *arq, Cliente *c, int pos) {
    NoCliente *retorno = NULL;

    if(pos == -1) {
        fseek(arq, 0, SEEK_END);
    }
    else {
        fseek(arq, pos, SEEK_SET);
    }
    if(fwrite(c, sizeof(Cliente), 1, arq) && ftell(arq) != -1){
        retorno = criaNoCliente(c, (ftell(arq) - sizeof(Cliente)) /
             sizeof(Cliente));
        fflush(arq); // força os dados a serem escritos
    }
    return retorno;
}

// retorna 0 se nao conseguir ler
int leCliente(FILE *arq, long int pos, Cliente *cliente) {

    fseek(arq, pos, SEEK_SET);
    if(fread(cliente, sizeof(Cliente), 1, arq) != 1) {
        return 0;
    }
    return 1;
}

void limpaArquivoCliente(FILE *arq) {
    FILE *aux;
    int const TAM = 25;
    int nLidos = 0, nEscrever = 0;
    Cliente lidos[25], escrever[25];

    aux = abreArquivo("cliente.old");
    fseek(arq, 0, SEEK_SET);
    do {
        nLidos = fread(lidos, sizeof(Cliente), TAM, arq);
        nEscrever = 0;
        for(int i = 0; i < nLidos; i++) {
            if(lidos[i].status) {
                escrever[nEscrever++] = lidos[i];
            }
        }

        if(nEscrever != fwrite(escrever, sizeof(Cliente), nEscrever, aux)) {
            printf("Erro ao executar limpeza no arquivo %s\n\n", CLIENTE_ARQ);
        }
    } while(nLidos == TAM);

    fflush(aux);
    fechaArquivo(arq, CLIENTE_ARQ);
    fechaArquivo(aux, "cliente.old");
    remove(CLIENTE_ARQ);
    rename("cliente.old", CLIENTE_ARQ);
}

//--io------------------------------------------------------------------------

void imprimeCliente(Cliente *c, int pos) {
    char formatado[CPF_FORMAT];

    if(pos) { // so imprime se pos != 0
        printf("Cliente No. %d\n", pos);
    }
    printf("Nome: %s\n", c->nome);
    formataCPF(formatado, c->cpf);
    printf("CPF: %s\n", formatado);
    printf("Telefone: %s\n", c->telefone);
    printf("E-mail: %s\n\n", c->email);
}

void formataCPF(char *formatado, char *cpf) {
    int j = 0, i = 0;

    while(cpf[i] != '\0') {
        formatado[j++] = cpf[i];
        if(i == 2 || i == 5) {
            formatado[j++] = '.';
        } else if(i == 8) {
            formatado[j++] = '-';
        }
        ++i;
    }
    formatado[j] = '\0';
    
}

// imprime mensagens de acordo com o resultado dasa funcoes buscar
// para tornar as funcoes o mais genericaas possiveis entre os modulos
int validaProcuraCliente(int retorno) {
    if(retorno == -1) {
        printf("Cliente com este cpf nao existe\n\n");
        return 0;
    } else if(retorno == 0) {
        printf("Erro ao ler cliente do arquivo\n\n");
        return 0;
    } 
    return 1;
}

//--Menu----------------------------------------------------------------------

int menuClientes() {
    int resp;

    printf("|=================================|\n");
    printf("|       Menu Clientes             |\n");
    printf("|                                 |\n");
    printf("|  %d - Cadastrar                  |\n", CADASTRAR);
    printf("|  %d - Remover                    |\n", REMOVER);
    printf("|  %d - Alterar                    |\n", ALTERAR);
    printf("|  %d - Procurar por CPF           |\n", PROCURA_CPF);
    printf("|  %d - Procurar por Nome          |\n", PROCURA_NOME);
    printf("|  %d - Imprime Todos Clientes     |\n", EXIBIR_TODOS);
    printf("|  %d - Voltar                     |\n", VOLTAR);
    printf("|                                 |\n");
    printf("|=================================|\n\n");
    printf("Sua escolha: ");
    scanf("%d", &resp);
    limpaBuffer();

    return resp;
}

void loopClientes(FILE *arq, NoCliente **raizCliente) {
    int m, n;
    char cpf[CPF_TAM], nome[NOME_TAM];

    do {
        m = menuClientes();
        switch(m) {
            case CADASTRAR:
                limpaTela();
                if(pegaDado(cpf, CPF)) {
                    cadastrarCliente(arq, raizCliente, cpf);
                }
                break;
            case REMOVER:
                if(pegaDado(cpf, CPF)) {
                    removerCliente(arq, raizCliente, cpf);
                }
                break;
            case ALTERAR:
                if(pegaDado(cpf, CPF)) {
                    alterarCliente(arq, raizCliente, cpf);
                }
                break;
            case PROCURA_CPF:
                limpaTela();
                if(pegaDado(cpf, CPF)) {
                    buscaCPF(arq, *raizCliente, cpf);
                }
                break;
            case PROCURA_NOME:
                limpaTela();
                if(pegaDado(nome, NOME)) {
                    buscaNome(arq, nome);
                }
                break;
            case EXIBIR_TODOS: 
                limpaTela();
                n = 0;
                exibirTodos(arq, *raizCliente, &n);
                break;
            case VOLTAR:
                limpaTela();
                break;  
            default: 
                limpaTela();
                printf("Opcao invalida!\n");
                break;
        }
    } while(m != VOLTAR);
}
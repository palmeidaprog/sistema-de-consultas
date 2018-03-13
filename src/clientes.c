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
    printf("Cliente %s foi cadastrado com sucesso\n\n", cpf);
}

void exibirTodos(FILE *arq, NoCliente *raiz) {
    Cliente cliente;
    int pos = 0;

    if(raiz == NULL) {
        printf("Não existe clientes cadastrados\n\n");
        return ;
    }

    if(ehFolha(raiz)) {
        leCliente(arq, raiz->indice * sizeof(Cliente), &cliente);
        imprimeCliente(&cliente, ++pos);
        return ;
    }
    if(raiz->esq != NULL) {
        exibirTodos(arq, raiz->esq);
    }
    if(raiz->dir != NULL) {
        exibirTodos(arq, raiz->dir);
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
    // TODO: Resolver problema de ENTER no nome
    pegaDadoCliente(cl->nome, NOME);
    pegaDadoCliente(cl->telefone, TELEFONE);
    pegaDadoCliente(cl->email, EMAIL);
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
    pegaDadoCliente(cliente.telefone, TELEFONE);
    pegaDadoCliente(cliente.email, EMAIL);
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
    NoCliente *pos;
    Cliente cliente;

    pos = buscar(raiz, cpf);
    if(pos == NULL) {
        printf("Cliente com cpf %s nao existe\n\n", cpf);
    } else {
        if(!leCliente(arq, pos->indice * sizeof(Cliente), &cliente)) {
            printf("Erro ao ler cliente do arquivo\n\n");
        } else {
            imprimeCliente(&cliente, 0);
        }
    }
}

//--Arquivo-------------------------------------------------------------------

int buscaPorNome(FILE *arq, char *nome) {
    int const TAM = 100;
    int n;
    Cliente clientes[TAM];

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
int leCliente(FILE *arq, long long pos, Cliente *cliente) {

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
    Cliente lidos[TAM], escrever[TAM];

    aux = abreArquivo("aux.dat");
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
    fechaArquivo(aux, "aux.dat");
    remove(CLIENTE_ARQ);
    rename("aux.dat", CLIENTE_ARQ);
}

//--io------------------------------------------------------------------------

void imprimeCliente(Cliente *c, int pos) {
    if(pos) { // so imprime se pos != 0
        printf("Cliente No. %d\n", pos);
    }
    printf("Nome: %s\n", c->nome);
    printf("CPF: %s\n", c->cpf);
    printf("Telefone: %s\n", c->telefone);
    printf("E-mail: %s\n\n", c->email);
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
    int m;
    char cpf[CPF_TAM], nome[NOME_TAM];

    do {
        m = menuClientes();
        switch(m) {
            case CADASTRAR:
                limpaTela();
                if(pegaDadoCliente(cpf, CPF)) {
                    cadastrarCliente(arq, raizCliente, cpf);
                }
                break;
            case REMOVER:
                limpaTela();
                if(pegaDadoCliente(cpf, CPF)) {
                    removerCliente(arq, raizCliente, cpf);
                }
                break;
            case ALTERAR:
                limpaTela();
                if(pegaDadoCliente(cpf, CPF)) {
                    alterarCliente(arq, raizCliente, cpf);
                }
                break;
            case PROCURA_CPF:
                limpaTela();
                if(pegaDadoCliente(cpf, CPF)) {
                    buscaCPF(arq, *raizCliente, cpf);
                }
                break;
            case PROCURA_NOME:
                limpaTela();
                if(pegaDadoCliente(nome, NOME)) {
                    buscaNome(arq, nome);
                }
                break;
            case EXIBIR_TODOS: 
                limpaTela();
                exibirTodos(arq, *raizCliente);
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

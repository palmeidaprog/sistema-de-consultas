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
}

void exibirTodos(FILE *arq, NoCliente *raiz) {
    Cliente cliente;
    int pos = 0;

    if(raiz == NULL) {
        printf("Não existe clientes cadastrados\n\n");
        return ;
    }

    if(ehFolha(raiz)) {
        leCliente(arq, raiz, &cliente);
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
        return;
    }

    if(!leCliente(arq, pos, &cliente)) {
        printf("Erro ao ler o arquivo %s\n\n", CLIENTE_ARQ);
    }
    cliente.status = 0;
    escreveCliente(arq, &cliente, pos->indice * sizeof(Cliente));
    removerIndiceCliente(raiz, pos);
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

//--Arvore--------------------------------------------------------------------

void criaArvoreCliente(FILE *arq, NoCliente **raizCliente) {
    int const TAM = 25;
    Cliente v[TAM];
    NoCliente *no;
    long long pos = 0, n;

    n = fread(v, sizeof(Cliente), TAM, arq);
    while(n > 0) {
        if(!feof(arq) && n != TAM) {
            printf("Erro de leitura no arquivo %s\n", CLIENTE_ARQ);
            return ;
        }
        for(int i = 0; i < n; i++) {
            if(v[i].status) {
                no = criaNoCliente(&v[i], pos);
                inserirIndiceCliente(&(*raizCliente), no);
            }
            ++pos;
        }
        n = fread(v, sizeof(Cliente), TAM, arq);
    }
}

void inserirIndiceCliente(NoCliente **raizCliente, NoCliente *no) {
    if(*raizCliente == NULL) { // arvore vazia
        *raizCliente = no;
        return;
    }

    if(strcmp((*raizCliente)->cpf, no->cpf) > 0) {
        inserirIndiceCliente(&((*raizCliente)->esq), no);
    } else {
        inserirIndiceCliente(&((*raizCliente)->dir), no);
    }

    return ;
}

NoCliente *criaNoCliente(Cliente *c, long long int pos) {
    NoCliente *no = NULL;
    
    if(pos < 0) {
        return NULL;
    }
    no = (NoCliente *) malloc(sizeof(NoCliente));
    no->dir = NULL;
    no->esq = NULL;
    strcpy(no->cpf, c->cpf);
    no->indice = pos;
    return no;
}

void removerIndiceCliente(NoCliente **raizCliente, NoCliente *remov) {
    NoCliente *maior;

    if(ehFolha(remov)) {
        removeFolhaCliente(raizCliente, remov);
    } else { // nao é folha
        maior = maiorIndiceCliente(*raizCliente);
        copiaNoCliente(remov, maior); // copia maior no lugar do removido
        if(!ehFolha(maior)) {
            moveNoCliente(maior, maior->esq); // move filho
        }
    }
}

void removeFolhaCliente(NoCliente **raiz, NoCliente *remov) {
    if(*raiz == remov) {
        free(*raiz);
        *raiz = NULL;
    } else if(strcmp(remov->cpf, (*raiz)->cpf) > 0) {
        removeFolhaCliente(&((*raiz)->dir), remov);
    } else {
        removeFolhaCliente(&((*raiz)->esq), remov);
    }
}

void copiaNoCliente(NoCliente *destino, NoCliente *origem) {
    strcpy(destino->cpf, origem->cpf);
    destino->indice = origem->indice;
}

void moveNoCliente(NoCliente *destino, NoCliente *origem) {
    copiaNoCliente(destino, origem);
    destino->esq = origem->esq;
    destino->dir = origem->dir;
    free(origem);
}

NoCliente *maiorIndiceCliente(NoCliente *raiz) {
    if(raiz == NULL) {
        return NULL;
    }

    while(!ehFolha(raiz)) {
        raiz = raiz->dir;
    }
    return raiz;
}

int ehFolha(NoCliente *no) {
    if(no->dir == NULL && no->esq == NULL) {
        return 1;
    }
    return 0;
}

NoCliente *buscar(NoCliente *raiz, char *cpf) {
    int cmp;

    if(raiz == NULL) {
        return NULL;
    }
    while(ehFolha(raiz)) {
        cmp = strcmp(cpf, raiz->cpf);
        if(cmp == 0) {
            return raiz;
        } else if(cmp > 0) {
            raiz = raiz->dir;
        } else {
            raiz = raiz->esq;
        }
    }
    return NULL;   
}

//--Arquivo-------------------------------------------------------------------

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
        retorno = criaNoCliente(c, (ftell(arq) - sizeof(NoCliente)) /
             sizeof(NoCliente));
        fflush(arq); // força os dados a serem escritos
    }
    return retorno;
}

// retorna 0 se nao conseguir ler
int leCliente(FILE *arq, NoCliente *no, Cliente *cliente) {
    fseek(arq, no->indice * sizeof(Cliente), SEEK_SET);
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

        if(nEscrever != fwrite(escrever, sizeof(Cliente), nEscrever, arq)) {
            printf("Erro ao executar limpeza no arquivo %s\n\n", CLIENTE_ARQ);
        }
    } while(nLidos == TAM);

    fechaArquivo(arq, CLIENTE_ARQ);
    fechaArquivo(aux, "aux.dat");
    remove(CLIENTE_ARQ);
    rename("aux.dat", CLIENTE_ARQ);
}

//--Validações----------------------------------------------------------------

int validaCPF(char *cpf) {
    int primeiroDigito = 0, segundoDigito = 0, multiplicador = 11, i = 0;
    char cpfInvalidos[10][11] = { "00000000000", "11111111111", "22222222222", 
        "33333333333", "44444444444", "55555555555", "66666666666", 
        "77777777777", "88888888888", "99999999999"};

    if(strlen(cpf) != 11) {
        return 0;
    }
    
    // verifica se todos digitos sao iguais
    for(int i = 0; i < 10; i++) {
        if(strcmp(cpfInvalidos[i], cpf) == 0) {
            return 0;
        }
    }

    while(cpf[i] != '\0') {
        if(i <= 8) {
            primeiroDigito += (cpf[i] - '0') * (multiplicador - 1);
        }
            
        if(i <= 9) {
            segundoDigito += (cpf[i] - '0') * multiplicador;
        }

        if(!ehNumero(cpf[i])) { // contem nao numeros
            return 0;
        }
        --multiplicador;
        ++i;
    }
    primeiroDigito = restoCPF(primeiroDigito);
    segundoDigito = restoCPF(segundoDigito);

    if(primeiroDigito != (cpf[9] - '0') || segundoDigito != (cpf[10] - '0')) {
        return 0;
    }
    return 1;
}

// função suporte de validaCPF()
int restoCPF(int x) {
    x = x * 10 % 11;
    return (x == 10) ? 0 : x;
} 

int validaNome(char *nome) {
    int i = 0;

    while(nome[i] != '\0') {
        if(!ehLetra(nome[i]) && !ehEspaco(nome[i])) {
            return 0;
        }
    }
    return 1;
}

int validaTelefone(char *telefone) {
    int i = 0;

    while(telefone[i] != '\0') {
        if(!ehEspaco(telefone[i])) {
            return 0;
        }
        ++i;
    }
    return 1;
}

int ehEspaco(char c) {
    return (c == ' ');
}

int ehNumero(char c) {
    if(c >= 48 || c <= 57) {
        return 1;
    }
    return 0;
}

int ehLetra(char c) {
    if((c >= 'A' && c <= 'Z') && (c >= 'a' && c <= 'z')) {
        return 1;
    }
    return 0;
}

// apenas encontra . - _ letras e numeros. Arroba tem que existir e tem que 
// existir um ponto apos a arroba (nao pode ser o ultimo caractere)
int validaEmail(char *email) {
    int arroba = 0, pontoAposArroba = 0, i = 0, letraAntesArroba = 0;

    if(!ehLetra(email[0]) && !ehNumero(email[0])) {
        return 0;
    }

    while(email[i] != '\0') {
        if(!arroba) {
            if(email[i] == '@') {
                // tem que existir letra antes da arroba e arroba nao pode
                // ser o ultimo caractere
                if(!letraAntesArroba || email[i+1] == '\0') {
                    return 0;
                }
                arroba = 1;
            }
            // antes da arroba tem que ter pelo menos 1 letra
            if(!letraAntesArroba && ehLetra(email[i])) {
                letraAntesArroba = 1;
            }
        }
        // caracteres invalidos no email
        if(!validoNoEmail(email[i])) {
            if(arroba || (!arroba && email[i] != '_')) { // _ antes do @
                return 0;
            }
        }
        ++i;
    }
    if(!arroba || !letraAntesArroba || !pontoAposArroba) {
        return 0;
    }
    return 1;
}

int validoNoEmail(char c) {
    if(ehNumero(c) || ehLetra(c) || c == '-' || c == '.') {
        return 1;
    }
    return 0;
}

// valida tudo
int validacao(char *aValidar, ClienteTipo tipo) {
    switch(tipo) {
        case EMAIL: 
            return validaEmail(aValidar);
        case CPF: 
            return validaCPF(aValidar);
        case NOME: 
            return validaNome(aValidar);
        default: // TELEFONE
            return validaTelefone(aValidar);
    }
}

//--io------------------------------------------------------------------------

void pegaDadoCliente(char *dado, ClienteTipo tipo) { 
    int erro = 0;
    char str[50]; 
    
    do {
        if(erro) {
            pegaErro(tipo, str);
            printf("%s", str);
        }
        pegaMensagem(tipo, str);
        printf("%s", str);
        pegaString(dado, pegaTamanho(tipo));
        erro =1;
    } while(!validacao(dado, tipo));
}

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
    char cpf[CPF_TAM];

    do {
        m = menuClientes();
        switch(m) {
            case CADASTRAR:
                limpaTela();
                pegaDadoCliente(cpf, CPF);
                cadastrarCliente(arq, raizCliente, cpf);
                break;
            case REMOVER:
                limpaTela();
                pegaDadoCliente(cpf, CPF);
                removerCliente(arq, raizCliente, cpf);
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

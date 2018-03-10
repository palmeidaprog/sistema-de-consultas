/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "validacao.h"
#include "clientes.h"

int pegaTamanho(ClienteTipo tipo) {
    switch(tipo) {
        case EMAIL: 
            return EMAIL_TAM;
        case CPF: 
            return CPF_TAM;
        case NOME: 
            return NOME_TAM;
        default:  // TELEFONE
            return TELEFONE_TAM;
    }
}

void pegaErro(ClienteTipo tipo, char *erro) {
    switch(tipo) {
        case EMAIL: 
            strcpy(erro, "ERRO: Email deve conter apenas uma arroba.\n");
            break;
        case CPF: 
            strcpy(erro, "CPF Inválido\n\n");
            break;
        case NOME:
            strcpy(erro, "ERRO: Nome contem apenas letras e espacos.\n") ;
            break;
        default: // TELEFONE
            strcpy(erro, "ERRO: Numero de telefone apenas contem numeros.\n");
            break;
    }
}

void pegaMensagem(ClienteTipo tipo, char *msg) {
    switch(tipo) {
        case EMAIL: 
            strcpy(msg, "Insira o e-mail do cliente: ");
            break;
        case CPF: 
            strcpy(msg, "Insira o CPF (Sem pontos e hifen): ");
            break;
        case NOME:
            strcpy(msg, "Insira o nome do cliente: ");
            break;
        default:  // TELEFONE
            strcpy(msg, "Insira o telefone do cliente: ");
            break;
    }
}

// so retorna 0 caso validacao do CPF seja invalida
int pegaDadoCliente(char *dado, ClienteTipo tipo) { 
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
        // CPF nao fica preso no loop
        if(tipo == CPF && !validacao(dado, tipo)) { 
            pegaErro(tipo, str);
            printf("%s", str);
            return 0;
        }
    } while(tipo != CPF && !validacao(dado, tipo));
    return 1;
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
        ++i;
    }
    return 1;
}

int validaTelefone(char *telefone) {
    int i = 0;

    while(telefone[i] != '\0') {
        if(!ehNumero(telefone[i])) {
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
    if(c >= 48 && c <= 57) {
        return 1;
    }
    return 0;
}

int ehLetra(char c) {
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return 1;
    }
    return 0;
}

// apenas encontra . - _ letras e numeros. Arroba tem que existir e tem que 
// existir um ponto apos a arroba (nao pode ser o ultimo caractere)
int validaEmail(char *email) { // FIXME: Corrigir validacao
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
                ++i;
                continue;
            }
            // antes da arroba tem que ter pelo menos 1 letra
            if(!letraAntesArroba && ehLetra(email[i])) {
                letraAntesArroba = 1;
            }
        }
        if(arroba && email[i] == '.') {
            pontoAposArroba = 1;
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
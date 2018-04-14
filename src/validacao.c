/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "validacao.h"

int pegaTamanho(Tipo tipo) {
    switch(tipo) {
        case CRM: 
            return CRM_TAM;
        case EMAIL: 
            return EMAIL_TAM;
        case CPF: 
            return CPF_TAM;
        case NOME:
            return NOME_TAM;
        case TELEFONE:  
            return TELEFONE_TAM;
        default: // HORA / MIN
            return 0; 
    }
}

void pegaErro(Tipo tipo, char *erro) {
    switch(tipo) {
        case CRM: 
            strcpy(erro, "CRM Invalido\n\n");
            break;
        case EMAIL: 
            strcpy(erro, "ERRO: Email deve conter apenas uma arroba.\n");
            break;
        case CPF: 
            strcpy(erro, "CPF Inválido\n\n");
            break;
        case NOME:
            strcpy(erro, "ERRO: Nome contem apenas letras e espacos.\n") ;
            break;
        case HORA:
            strcpy(erro, "ERRO: Hora deve ser um numero entre 00 e 23.\n") ;
            break;
        case MIN:
            strcpy(erro, "ERRO: Minutos deve ser um numero entre 00 e 59.\n") ;
            break;
        default: // TELEFONE
            strcpy(erro, "ERRO: Numero de telefone apenas contem numeros.\n");
            break;
    }
}

void pegaMensagem(Tipo tipo, char *msg) {
    switch(tipo) {
        case CRM: 
            strcpy(msg, "Insira o CRM do Medico: ");
            break;
        case EMAIL: 
            strcpy(msg, "Insira o e-mail: ");
            break;
        case CPF: 
            strcpy(msg, "Insira o CPF (Sem pontos e hifen): ");
            break;
        case NOME:
            strcpy(msg, "Insira o nome: ");
            break;
        case HORA:
            strcpy(msg, "Insira a hora: ");
            break;
        case MIN:
            strcpy(msg, "Insira os minutos: ");
            break;
        default:  // TELEFONE
            strcpy(msg, "Insira o telefone: ");
            break;
    }
}

// so retorna 0 caso validacao do CPF/CRM seja invalida
int pegaDado(char *dado, Tipo tipo) { 
    int erro = 0;
    char str[50]; 
    
    do {
        if(erro) {
            pegaErro(tipo, str);
            printf("%s", str);
        }
        pegaMensagem(tipo, str);
        printf("%s", str);
        if(tipo == CPF) {
        (dado, pegaTamanho(tipo));
        } else {
            pegaString(dado, pegaTamanho(tipo));
        }
        erro =1;
        // CPF nao fica preso no loop
        if((tipo == CPF || tipo == CRM) && !validacao(dado, tipo)) { 
            pegaErro(tipo, str);
            printf("%s", str);
            return 0;
        }
    } while(tipo != CPF && tipo != CRM && !validacao(dado, tipo));
    return 1;
}

int pegaInt(Tipo tipo) {
    int erro = 0;
    int dado;
    char str[50];

    do {
        if(erro) {
            pegaErro(tipo, str);
            printf("%s", str);
        }
        pegaMensagem(tipo, str);
        printf("%s", str);
        scanf("%d", &dado);
        limpaBuffer();
        erro = 1;
    } while(!validaInt(tipo, dado));
    
    return dado;
}

int confirmacao(char *msg) {
    char resp;

    do {
        printf("%s (S/N) ", msg);
        scanf("%c", &resp);
        limpaBuffer();
    } while(resp != 's' && resp != 'n');
    return (resp == 's');
}


//--Validações----------------------------------------------------------------

int validaInt(Tipo tipo, int dado) {
    switch(tipo) {
        case HORA:
            return validaHora(dado);
        default: // MIN
            return validaMinuto(dado);
    }
}

int validaHora(int hora) {
    if(hora < 0 || hora > 23) {
        return 0;
    }
    return 1;
}

int validaMinuto(int minuto) {
    if(minuto < 0 || minuto > 59) {
        return 0;
    }
    return 1;
}

int validaCRM(char *crm) {
    int estado = 0;
    char estados[][2] = { "AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", 
        "GO", "MA", "MT", "MS", "MG", "PA", "PB", "PR", "PE", "PI", "RJ", 
        "RN", "RS", "RO", "RR", "SC", "SP", "SE", "TO" };
    size_t tamanho;
    
    tamanho = strlen(crm);
    if(tamanho < 3 || tamanho > 8) {
        return 0;
    }

    for(int i = 0; i < 27; i++) {
        if(estados[i][0] == crm[0] && estados[i][1] == crm[1]) {
            estado = 1;
            break;
        }
    }

    if(!estado) {
        return 0;
    }

    tamanho -= 1; // funcionar como indice
    for(size_t i = 2; i < tamanho; i++) {
        if(!ehNumero(crm[i])) {
            return 0;
        }
    }
    return 1;
}

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

    trim(nome);
    if(strlen(nome) <= 1) {
        return 0;
    }

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
int validacao(char *aValidar, Tipo tipo) {
    switch(tipo) {
        case CRM: 
            return validaCRM(aValidar);
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

// funcao suporte
void trim(char *str) {
    int i = 0, j = 0, espacoAntes = 0;
    char novaString[NOME_TAM];

    while(str[i] != '\0' && isspace(str[i])) {
        ++i;
    }

    while(str[i] != '\0') {
        if(!isspace(str[i])) {
            novaString[j++] = str[i];
            espacoAntes = 0;
        } else {
            if(!espacoAntes) {
                novaString[j++] = str[i];
            }
            espacoAntes = 1; 
        }
        ++i;
    }
    if(novaString[j - 1] == ' ') {
        novaString[j-1] = '\0';
    } else {
        novaString[j] = '\0';
    }
    strcpy(str, novaString);
}
#ifndef CONSULTAS_TYPES_H
#define CONSULTAS_TYPES_H

#define CRM_TAM 9 // 8 + 1
#define CPF_TAM 13 // + 1 para o /0
#define CONSULTAS_ARQ "consultas.dat" 

#include "tempo.h"

typedef enum Status {
    ATIVO,
    CANCELADO,
    ATENDIDO
} Status;

typedef struct Consulta {
    char clienteCpf[CPF_TAM];
    char medicoCrm[CRM_TAM];
    Data data;
    Turno turno;
    Status status;
    int codigo; // muda toda vez que a arvore é remontada
} Consulta;

// tipo de arvore_consultas.h (No da arvore)
typedef struct NoConsulta {
    Data data;    
    int codigo;
    int indice;
    char medicoCrm[CRM_TAM];
    struct NoConsulta *dir, *esq;
} NoConsulta;

#endif // CONSULTAS_TYPES_H
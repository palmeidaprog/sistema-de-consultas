#ifndef CONSULTAS_TYPES_H
#define CONSULTAS_TYPES_H

#define CRM_TAM 9 // 8 + 1
#define CPF_TAM 13 // + 1 para o /0

#include "tempo.h"

typedef struct Consulta {
    char clienteCpf[CPF_TAM];
    char medicoCrm[CRM];
    Data data;
    Turno turno;
    int codigo;
} Consulta;

// tipo de arvore_consultas.h (No da arvore)
typedef struct NoConsulta {
    Data data;    
    int codigoConsulta;
    int indice;
    struct NoConsulta *dir, *esq;
} NoConsulta;

#endif // CONSULTAS_TYPES_H
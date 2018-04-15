/*
 * UNICAP - Universidade Catolica de Pernambuco
 * Pratica de Programação
 * Prof: Me. Ana Eliza Moura
 * Projeto 01 - Sistema de MArcação de Consultas
 * Aluno: Paulo R. Almeida Filho
 * E-mail: pauloalmeidaf@gmail.com
 */

#include "consultas.h"

void marcarConsulta(FILE *arqCliente, FILE *arqMedico, NoCliente *raizCliente,
            NoMedico *raizMedico) {
    Consulta consulta;
    Cliente cliente;
    Medico medico;
    char cpf[CPF_TAM], crm[CRM_TAM];
    
    printf("Marcar Consulta:\n");

    do {
        if(pegaDado(cpf, CPF)) {
            if(validaProcuraCliente(buscarCliente(arqCliente, raizCliente, cpf, 
                &cliente))) {
                strcpy(consulta.clienteCpf, cpf);
                break;
            }
        }
    } while(confirmacao("Deseja tentar outro CPF?"));

    do {
        if(pegaDado(crm, CRM)) {
            if(validaProcuraMedico(buscaMedico(arqMedico, raizMedico, crm, 
                &medico))) { 
                strcpy(consulta.medicoCrm, crm);
                break;
            }
        }
    } while(confirmacao("Deseja tentar outro CRM?"));

    // TODO: terminar marcarConsulta
   
}

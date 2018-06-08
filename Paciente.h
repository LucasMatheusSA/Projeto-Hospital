//Paciente.h
#include "Types.h"

void cadastrar_paciente(FILE * arq, TNO **indice, char cpf[]);//Cadastra paciente 
void alterar_paciente(FILE * arq, TNO **indice, char cpf[]);//Altera paciente
void exibir(FILE * arq, TNO *indice, char cpf[]);//exibir de pacientes
void remover(FILE * arq, TNO **indice, char cpf[],FILE *arq2);//remove Paciente
int consultar_nome_paciente(FILE * arq, char nomeAux[], int pos);//Consulta Paciente por Nome
void manutencao(FILE *arq, char nome[]);//Manutenção do arq Paciente
void montar_tree_paciente(FILE *arq, TNO **indice);//Monta a arvore Paciente
//Consulta.h
#include "Types.h"

void marcar_consulta(char cpf[12],char crm[9],FILE *arqM,FILE *arqCon,int opp);//marca consulta
void Consultar_paciente(FILE *arq,char crm[9],int dia,int mes,int ano,int turno,FILE *arqP,TNO *treeP);//consulta paciente
void Consultar_consulta(FILE *arq,char cpf[12],FILE *arqM,TNO *treeM);// para consultar a consulta 
int procurar_fila(Data data,char crm[9],int turno,FILE *arqCon);// procura na fila se a lusta de espera ja esta cheia 
int busca_consulta_medico(FILE *arq,char cod[]);// busca por consulta medico
int busca_consulta_paciente(FILE *arq,char cod[]);// busca ´por paciente 
void desmarcar_consulta(char cpf[],char crm[],FILE *arq);// desmarcar consulta 
void manutencao_consulta(FILE *arq);// manutencao do arquivo de consultas
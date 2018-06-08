//Medico.h
#include "Types.h"

void horario(Medico *medicoDaVez);// horarios
void CRM(char crm[]);// pega CRM
int validar_crm(char crm[]);//valida crm
int validaSigla(char crm[]);//valida a sigla do crm 
void cadastrar_medico(FILE * arqM, TNO **indice, char CRM[]);// cadastra medico
void busca_especialidade(FILE * arq, char especialidade[]);// busca por especialidade
void consultar_nome_medico(FILE * arq, char nomeAux[]);//consulta por nome
void removerMed(FILE * arq, TNO **indice, char crm[],FILE *arq2);//remover medico
void alterar_medico(FILE * arq, TNO **indice, char crm[]);//alterar medico
void manutencao_medico(FILE *arqM, char nome[]);// manutencao do arquivo  de emdicos 
void montar_tree_medicos(FILE *arq, TNO **raiz);// monta a arvore de medico
void exibir_medico(FILE * arq, TNO *indice, char crm[]);//exibir de medico
void exibirM(FILE * arq, TNO *indice, char cpf[]);//Exibir dados do medico
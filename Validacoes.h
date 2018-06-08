//Validacoes.h
#include "Types.h"

FILE *criarArquivo(char nome[]);//Abre ou Cria arquivo
void NOME(char nome[]);//Função para pedir nome
int validar_nome(char nome[]);//Valida Nome
void formata_nome(char nome[]);//Formata Nome
int validar_fone(char fone[]);//Valida telefone
void CPF(char cpf[]);//Função para pedir cpf
int validar_cpf(char cpf[]);//Validar cpf
int dia_semana(Data d);//Validar dia da semana
int valiar_email(char email[]);//Validar Email
int dia_semana(Data d);//retorna o dia da semana 
int ano_(int ano);//valida ano
int validar_data_(int dia, int mes, int ano);//valida data em geral
int validar_dia(int dia, int mes, int ano, int turno);//valida o dia para medico 
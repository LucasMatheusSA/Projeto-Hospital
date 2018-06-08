//Types.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define T 100
#define TRUE 1
#define FALSE 0
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_WARNINGS

#ifndef ESTRUTURAS
#define ESTRUTURAS

typedef struct Data{
	int dia,mes,ano;
}Data;

typedef struct clientes {
    char CPF[12], nome[T], fone[16], email[T];
    int status;
}Paciente;
 
typedef struct medicos{
    char CRM[9], nome[T], fone[16], email[T], tabela[2][5],  especialidade[50];
    int status, turno;
}Medico;

typedef struct consultas{
	char crm[9], cpf[12], status[11];
	int dia, mes, ano, turno;
}Consulta;


typedef struct noQueue{
       Consulta info;
       struct noQueue *prox;
}NoQueue;

typedef struct descritor {
      NoQueue * inicio, * fim;
}Descritor;

typedef Descritor * Queue;
#endif
 
#ifndef ARVORE
#define ARVORE
typedef struct noTree {
    char cpfORcrm[15];
    int pos, status;
    struct noTree *esq, *dir;
}TNO;
#endif

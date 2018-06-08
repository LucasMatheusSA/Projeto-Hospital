//Consulta.c
#include "Types.h"
#include "Fila.h"
#include "Paciente.h"
#include "Tree.h"
#include "Validacoes.h"
#include "Medico.h"

// para fins de teste mano
void marcar_consulta(char cpf[12],char crm[9],FILE *arqM,FILE *arqCon,int opp){
	Consulta aux;
	Data data;
	Medico auxM;
	char op;
	int resp,turno;
	strcpy(aux.cpf,cpf);
	strcpy(aux.crm,crm);
	printf("Digite a data da consulta:(Dia/Mes/Ano)\n");
	printf("Dia:");scanf("%d",&data.dia);printf("Mes:");scanf("%d",&data.mes);printf("Ano:");scanf("%d",&data.ano);
	printf("Digite o turno da consulta (0 - MANHA/1 - TARDE):");
	scanf("%d",&turno);
	resp=validar_dia(data.dia,data.mes,data.ano,turno);
	while(resp!=1){
		printf("Data ou turno invalido!\n");
		printf("Digite a data da consulta:(Dia/Mes/Ano)\n");
		printf("Dia:");scanf("%d",&data.dia);printf("Mes:");scanf("%d",&data.mes);printf("Ano:");scanf("%d",&data.ano);
		printf("Digite o turno da consulta (0 - MANHA/1 - TARDE):");
		scanf("%d",&turno);
		resp=validar_dia(data.dia,data.mes,data.ano,turno);
	}
	fseek(arqM,0,0);
	fseek(arqM, opp*sizeof(Medico),0);
	resp=fread(&auxM,sizeof(Medico),1,arqM);
	if(resp!=1){
		printf("Erro na leitura!\n");
	}else{
		resp=dia_semana(data);
		if(auxM.tabela[turno][resp]!='X'){
			printf("O medico nao pode atender nesta data ou turno!\n");
		}else{
			if(procurar_fila(data,crm,turno,arqCon)==FALSE){
				aux.dia=data.dia;aux.mes=data.mes;aux.ano=data.ano;aux.turno=turno;strcpy(aux.status,"ativo");
				fseek(arqCon,0,2);
				resp=fwrite(&aux,sizeof(Consulta),1,arqCon);
				if(!feof(arqCon) && resp!=1){
					printf("Erro de escrita!\n");
				}else{
					printf("Consulta marcada!\n");
				}
			}else{
				printf("A lista de pacientes para esta data e neste turno esta lotado!\n ");
				printf("Gostaria de esperar na fila (S/N)");op=getchar();fflush(stdin);op=toupper(op);
				if(op=='S'){
					aux.dia=data.dia;aux.mes=data.mes;aux.ano=data.ano;aux.turno=turno;strcpy(aux.status,"em espera");
					fseek(arqCon,0,2);
					resp=fwrite(&aux,sizeof(Consulta),1,arqCon);
					if(!feof(arqCon) && resp!=1){
						printf("Erro de escrita!\n");
					}
				}
			}
		}
	}
}

void Consultar_paciente(FILE *arq,char crm[9],int dia,int mes,int ano,int turno,FILE *arqP,TNO *treeP){
	Consulta aux;
	int resp;
	fseek(arq,0,0);
	printf("\nData:%d/%d/%d\t",dia,mes,ano);if(turno==0){printf("Turno: Manha \n");}else{printf("Turno: Tarde \n");}
	while(!feof(arq)){
		resp=fread(&aux,sizeof(Consulta),1,arq);
		if(feof(arq))break;
		if(resp!=1 && !feof(arq)){
			printf("Erro de leitura!\n");
		}else if(aux.dia==dia && aux.mes==mes && aux.ano==ano && aux.turno==turno && strcmp (aux.crm,crm)==0 && strcmp(aux.status,"ativo")==0){
			printf("CPF:%s",aux.cpf);
			exibir(arqP,treeP,aux.cpf);
		} 
	}
	printf("\n^ Resultado a cima ^\n");
}

void Consultar_consulta(FILE *arq,char cpf[12],FILE *arqM,TNO *treeM){
	Consulta aux;
	int resp;
	fseek(arq,0,0);
	while(!feof(arq)){
		resp=fread(&aux,sizeof(Consulta),1,arq);
		if(feof(arq))break;
		if(resp!=1 && !feof(arq)){
			printf("Erro de leitura!\n");
		}else if(strcmp (aux.cpf,cpf)==0 && strcmp(aux.status,"ativo")==0){
			printf("\nData:%d/%d/%d\t",aux.dia,aux.mes,aux.ano);if(aux.turno==0){printf("Turno: Manha \n");}else{printf("Turno: Tarde \n");}
			printf("CRM:%s",aux.crm);
			exibirM(arqM,treeM,aux.crm);
		} 
	}
	printf("\n^ Resultado a cima ^\n");
}

int procurar_fila(Data data,char crm[9],int turno,FILE *arqCon){
	int resp,qtd=0;
	Consulta aux;
	fseek(arqCon,0,0);
	while(!feof(arqCon)){
		resp=fread(&aux,sizeof(Consulta),1,arqCon);
		if(resp!=1 && !feof(arqCon)){
			printf("Erro na leitura!\n");
		}else{
			if(aux.ano == data.ano && aux.mes == data.mes && aux.dia == data.dia && strcmp(aux.crm,crm)==0 && aux.turno== turno){
				qtd++;
			}
		}
	}
	if(qtd<10){
		return FALSE;
	}else{
		return TRUE;
	}
}

int busca_consulta_medico(FILE *arq,char cod[]){
	Consulta aux;
	int resp;
	fseek(arq,0,0);
	while(!feof(arq)){
		resp=fread(&aux,sizeof(Consulta),1,arq);
		if(resp!=1 && !feof(arq)){
			printf("Erro na leitura!\n");
		}else{
			if(strcmp(cod,aux.crm)==0  && strcmp(aux.status,"ativo")==0){
				return TRUE;
			}
		}
	}
	return FALSE;
}

int busca_consulta_paciente(FILE *arq,char cod[]){
	Consulta aux;
	int resp;
	fseek(arq,0,0);
	while(!feof(arq)){
		resp=fread(&aux,sizeof(Consulta),1,arq);
		if(resp!=1 && !feof(arq)){
			printf("Erro na leitura!\n");
		}else{
			if(strcmp(cod,aux.cpf)==0  && strcmp(aux.status,"ativo")==0){
				return TRUE;
			}
		}
	}
	return FALSE;
}

void desmarcar_consulta(char cpf[],char crm[],FILE *arq){
	Consulta aux;
	int resp,qtd=0;
	fseek(arq,0,0);
	while(!feof(arq)){
		resp=fread(&aux,sizeof(Consulta),1,arq);
		if(feof(arq))break;
		if(resp!=1 && !feof(arq)){
			printf("Erro de leitura!\n");
		}
		else{
			if((strcmp(aux.cpf,cpf)==0 && strcmp(aux.crm,crm)==0) && strcmp(aux.status,"ativo")==0){
				strcpy(aux.status,"cancelada");
				fseek(arq,-1* (int)sizeof(Consulta),1);
				resp=fwrite(&aux,sizeof(Consulta),1,arq);
				if(resp!=1){
					printf("Erro de gravacao!\n");
				}else{
					qtd++;
				}
				break;
			}
		}
	}
	if(qtd==0){
		printf("Consultas nao existente!\n");return;
	}else{
		printf("Consultas desmarcadas!\n");
	}
	fseek(arq,0,0);
	while(qtd!=0 && !feof(arq)){
		resp=fread(&aux,sizeof(Consulta),1,arq);
		if(resp!=1 && !feof(arq)){
			printf("Erro de leitura!\n");
		}else{
			if(strcmp(aux.crm,crm)==0 && strcmp(aux.status,"em espera")==0){
				strcpy(aux.status,"ativo");
				fseek(arq,-1* (int)sizeof(Consulta),1);
				resp=fwrite(&aux,sizeof(Consulta),1,arq);
				if(resp!=1){
					printf("Erro de gravacao!\n");
				}else{
					qtd--;
				}
			}
		}
	}
}

void manutencao_consulta(FILE *arq){
	Consulta aux;
	int resp;
	fseek(arq,0,0);
	while(!feof(arq)){
		resp=fread(&aux,sizeof(Consulta),1,arq);
		if(resp!=1){
			printf("Erro de leitura!\n");
		}else{
			if(validar_dia(aux.dia,aux.mes,aux.ano, aux.turno)==0){
				strcmp(aux.status,"concluido");
				fseek(arq,-1*sizeof(Consulta),1);
				resp=fwrite(&aux,sizeof(Consulta),1,arq);
				if(resp!=1){
					printf("Erro na escrita!\n");
				}else{
					break;
				}
			}
		}
	}
}
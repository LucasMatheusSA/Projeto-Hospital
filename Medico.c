//Medico.c
#include "Types.h"
#include "Tree.h"
#include "Validacoes.h"
#include "Consulta.h"

void horario(Medico *medico){
	int i, j;
	for(i=0;i<2;i++){
		for(j=0;j<5;j++){
			if((medico)->tabela[i][j]!='X')
				(medico)->tabela[i][j]='_';
		}
	}
}

void CRM(char crm[]){
    int i;
	printf("\nDigite o CRM:");
    for (i = 0; i < 8; i = i + 1) {
        crm[i] = getche(); fflush(stdin);
        if (crm[i] == 13) {
            break;
        }
    }
	crm[0]=toupper(crm[0]);
	crm[1]=toupper(crm[1]);
    crm[i] = '\0';
	printf("\n");
}

int validaSigla(char crm[]){
    char aux[3];
    aux[0] = toupper(crm[0]);
    aux[1] = toupper(crm[1]);
    aux[2] = '\0';
    if(strcmp("AM", aux) == 0 || strcmp("AC", aux) == 0 || strcmp("AL", aux) == 0 ||
		strcmp("AP", aux) == 0 || strcmp("BA", aux) == 0 || strcmp("CE", aux) == 0 || 
		strcmp("DF", aux) == 0 || strcmp("ES", aux) == 0 || strcmp("GO", aux) == 0 || 
		strcmp("MA", aux) == 0 || strcmp("MT", aux) == 0 || strcmp("MS", aux) == 0 || 
		strcmp("MG", aux) == 0 || strcmp("PA", aux) == 0 || strcmp("PB", aux) == 0 || 
		strcmp("PR", aux) == 0 || strcmp("PE", aux) == 0 || strcmp("PI", aux) == 0 || 
		strcmp("RJ", aux) == 0 || strcmp("RN", aux) == 0 || strcmp("RS", aux) == 0 || 
		strcmp("RO", aux) == 0 || strcmp("RR", aux) == 0 || strcmp("SC", aux) == 0 || 
		strcmp("SP", aux) == 0 || strcmp("SE", aux) == 0 || strcmp("TO", aux) == 0)
		return 1;
    return 0;
}

int validar_crm(char crm[]){
    int i, tamanho=strlen(crm);
    if (tamanho < 3 || tamanho > 8)
        return 0;
    for(i = 2; i < tamanho; i++){
        if (!isdigit(crm[i]))
            return 0;
    }
    i = validaSigla(crm);
    if (i == 0)
        return 0;
    return 1;
}

void cadastrar_medico(FILE *arqM, TNO **indice, char CRM[]) {
    Medico m;
    int status, pos, local, opp = 0, turno,i=0, esp, tamanho, j;
    char auxNome[T];
    fseek(arqM, 0, 2);
    pos = buscar(*indice, CRM);
    if (pos == -1) {
        fseek(arqM, 0, 2);
        strcpy(m.CRM, CRM);
        NOME(auxNome);
        opp = validar_nome(auxNome);
        while (opp == 0) {
            printf("Digite um nome valido: ");
            NOME(auxNome);
            opp = validar_nome(auxNome);
        }
        formata_nome(auxNome);
        strcpy(m.nome, auxNome);
        printf("Digite o telefone: ");
        fgets(m.fone, 16, stdin);
        opp = validar_fone(m.fone);
        while (opp == 0) {
            printf("Digite um telefone valido: ");
			fgets(m.fone, 16, stdin);
            opp = validar_fone(m.fone);
        }
        printf("Digite o e-mail: ");
        fgets(m.email, 100, stdin);
        opp = valiar_email(m.email);
        while (opp == 0) {
            printf("Digite um e-mail valido: ");
            fgets(m.email, 100, stdin);
            opp = valiar_email(m.email);
        }
        printf("\n1 - Nutricionista\n2 - Cardiologista\n3 - pediatra\n4 - Neurologista\n5 - Clinico Geral\nEscolha a especialidade do medico:");
		scanf("%d",&esp);fflush(stdin);
		while(esp>5 || esp<1){
			printf("\n\nOpcao invalida!\n");
			printf("\n1 - Nutricionista\n2 - Cardiologista\n3 - pediatra\n4 - Neurologista\n5 - Clinico Geral\nEscolha a especialidade do medico:");
			scanf("%d",esp);fflush(stdin);
		}
		if(esp==1){strcpy(m.especialidade,"Nutricionista");}
		if(esp==2){strcpy(m.especialidade,"Cardiologista");}
		if(esp==3){strcpy(m.especialidade,"Pediatra");}
		if(esp==4){strcpy(m.especialidade,"Neurologista");}
		if(esp==5){strcpy(m.especialidade,"Clinico Geral");}
		tamanho=strlen(m.especialidade);
		m.especialidade[tamanho+1]='\0';
        printf("Digite o turno da consulta (0 - MANHA/1 - TARDE):");
        scanf("%d",&turno);fflush(stdin);
        while(turno>2 || turno<0){
            printf("Digite o turno da consulta (0 - MANHA/1 - TARDE):");
            scanf("%d",&turno);fflush(stdin);
        }
        if(turno==0){
            for(i=0;i<5;i++){
                printf("1 - Segunda\n2 - Terca\n3 - Quarta\n4 - Quinta\n5 - Sexta\n0 - Dias ja determinados.\n");
                scanf("%d",&turno);fflush(stdin);
                if(turno==0)
                    break;
                else if(turno<6 && turno>0){
                    m.tabela[0][turno-1]='X';
                }
                else{
                    printf("Digite um dia valido!\n");
                    i--;
                }
				for(j=0;j<5;j++){
					m.tabela[1][j]='_';
				}
            }
        }
        else{
            for(i=0;i<5;i++){
                printf("1 - Segunda\n2 - Terca\n3 - Quarta\n4 - Quinta\n5 - Sexta\n0 - Dias ja determinados.\n");
                scanf("%d",&turno);fflush(stdin);
                if(turno==0)
                    break;
                else if(turno<6 && turno>0){
                    m.tabela[1][turno-1]='X';
                }
                else{
                    printf("Digite um dia valido!\n");
                    i--;
                }
            }
        }
		horario(&m);
        m.status = 1;
        status = fwrite(&m, sizeof(Medico), 1, arqM);
        if (status != 1)
            printf("Erro de gravacao!\n");
        else{
            local = ftell(arqM) / sizeof(Medico) - 1;
            insert(indice, CRM, local); 
			printf("Medico cadastrado com sucesso!\n");
        }
    }
    else {
        printf("\nMedico ja cadastrado!\n");
    }

}

void busca_especialidade(FILE * arq, char especialidade[]){
	Medico m;
    int status, position, i=0, j=0;
    fseek(arq, 0, 0);
	printf("Especialidade procurada: %s\n\n", especialidade);
    while(1){
        status = fread(&m, sizeof(Medico), 1, arq);
        if(status != 1){
            if(!feof(arq))
                printf("Erro na leitura!\n");
			printf("\n^ Resultados a cima ^\n");
			return;
        }
        else{
			if(strcmp(m.especialidade,especialidade)==0 && m.status == 1){
                position = ftell(arq) / sizeof(Medico) - 1;
				printf("CRM:%s\nNome:%s\n\t--Tabela de atendimento--\n",m.CRM, m.nome);
				printf("\t\t S T Q Q S\n");
				for(i=0;i<2;i++){
					if(i==0)
						printf("\tManha-> |");
					else
						printf("\tTarde-> |");
					for(j=0;j<5;j++){
						printf("%c",m.tabela[i][j]);
						printf("|");
					}
					printf("\n");
				}
				printf("---------------------------\n");
			}
        }
    }
	printf("\n^ Resultados a cima ^\n");
}

void consultar_nome_medico(FILE * arq, char nomeAux[]){
    Medico m;
    int status, position, i=0, j=0;
    fseek(arq, 0, 0);
	status = fread(&m, sizeof(Medico), 1, arq);
	if(status != 1){
		if(!feof(arq))
			printf("Erro na leitura!\n");
		printf("Resultados de busca acima\n");
		return;
	}
	else{
		while(1){
			if(strcmp(nomeAux, m.nome) == 0 && m.status == 1) {
				position = ftell(arq) / sizeof(Medico) - 1;
				printf("CRM:%s\nEspecialidade:%s\nTelefone:%sEmail:%s\n\t--Tabela de atendimento--\n",m.CRM, m.especialidade, m.fone, m.email);
				printf("\t\t S T Q Q S\n");
				for(i=0;i<2;i++){
					if(i==0)
						printf("\tManha-> |");
					else
						printf("\tTarde-> |");
					for(j=0;j<5;j++){
						printf("%c",m.tabela[i][j]);
						printf("|");
					}
					printf("\n");
				}
				return;
			}
			status = fread(&m, sizeof(Medico), 1, arq);
			if(status != 1){
				if(!feof(arq))
					printf("Erro na leitura!\n");
				printf("\n^ Resultados a cima ^\n");
				return;
			}
		}
	}
}

void exibirM(FILE * arq, TNO *indice, char cpf[]) {
    Medico c;
    int pos, status;
    pos = buscar(indice, cpf);
    if (pos == -1)
        printf("\nContato nao cadastrado!\n");
    else {
        fseek(arq, pos * sizeof(Medico), 0);
        status = fread(&c, sizeof(Medico), 1, arq);
        if (status != 1)
            printf("Erro de leitura!\n");
        else {
            printf("\n\nNome: %s \n", c.nome);
            printf("Telefone: %s", c.fone);
            printf("Email: %s \n", c.email);
        }
    }
}


void removerMed(FILE * arq, TNO **indice, char crm[],FILE *arq2){
    Medico m;
    int pos, status;
	if(busca_consulta_medico(arq2,crm)==TRUE){
		printf("\nMedico nao pode ser removido pois esta marcado numa consulta!\n");return;
	}
    pos = buscar(*indice, crm);
    if(pos == -1){
        printf("\nMedico nao cadastrado!\n");
    }
    else{
        fseek(arq, pos * sizeof(Medico), 0);
        status = fread(&m, sizeof(Medico), 1, arq);
        if(status != 1){
            printf("Erro de leitura!\n");
        }
        else{
            m.status = 0;
            fseek(arq, -1*sizeof(Medico) , 1);
            status = fwrite(&m, sizeof(Medico), 1, arq);
            if(status != 1){
                printf("Erro na remocao!\n");
            }
            else{
                printf("\nMedico removido com sucesso!\n");
                removeTree(indice, crm);
            }
        }
    }

}

void alterar_medico(FILE * arq, TNO **indice, char crm[]){
	Medico m;
    int pos, status, opp = 0, i, j, turno, tamanho, esp;
    char auxNome[T], op;
    pos = buscar(*indice, crm);
    if (pos == -1)
        printf("\nContato nao cadastrado!\n");
    else{
        fseek(arq, pos * sizeof(Medico), 0);
        status = fread(&m, sizeof(Medico), 1, arq);
        if (status != 1)
            printf("Erro de leitura!\n");
        else{
            printf("Contato encontrado!\n");
            do{
                system("cls");
				printf("Nome: %s\nCRM: %s\nEspecialidade: %s\nTelefone: %sE-mail: %s\n", m.nome, m.CRM, m.especialidade, m.fone, m.email);
				printf("\t\t S T Q Q S\n");
				for(i=0;i<2;i++){
					if(i==0)
						printf("\tManha-> |");
					else
						printf("\tTarde-> |");
					for(j=0;j<5;j++){
						printf("%c",m.tabela[i][j]);
						printf("|");
					}
					printf("\n");
				}
                printf("1 - alterar nome \n2 - alterar telefone \n3 - alterar e-mail \n4 - alterar Especialidade\n5 - alterar horarios\n0 - Voltar\nDigite a opcao: ");
                op = getchar();fflush(stdin);
                switch (op){
                case'1':NOME(auxNome);
                    opp = validar_nome(auxNome);
                    while (opp == 0){
                        printf("Nome invalido!\n");
                        NOME(auxNome);
                        opp = validar_nome(auxNome);
                    }
                    formata_nome(auxNome);
                    strcpy(m.nome, auxNome);
                    printf("Nome alterado com sucesso!\n");
                    system("pause");
                    break;
                case'2':printf("Informe o novo telefone: ");
                    fgets(m.fone, 16, stdin);
                    opp = validar_fone(m.fone);
                    while (opp == 0){
                        printf("Digite um telefone valido: ");
                        fgets(m.fone, 100, stdin);
                        opp = validar_fone(m.fone);
                    }
                    printf("Telefone alterado com sucesso!\n");
                    system("pause");
                    break;
                case'3':printf("Informe o novo e-mail: ");
                    fgets(m.email, 100, stdin);
                    opp = valiar_email(m.email);
                    while(opp == 0){
                        printf("Digite um e-mail valido: ");
                        fgets(m.email, 100, stdin);
                        opp = valiar_email(m.email);
                    }
                    printf("e-mail alterado com sucesso!\n");
                    system("pause");
                    break;
                case'4':printf("1 - Nutricionista\n2 - Cardiologista\n3 - Pediatra\n4 - Neurologista\n5 - Clinico Geral\nEscolha a especialidade do medico:");
					scanf("%d",&esp);fflush(stdin);
					while(esp>5 || esp<1){
						printf("\n\nOpcao invalida!\n");
						printf("1 - Nutricionista\n2 - Cardiologista\n3 - Pediatra\n4 - Neurologista\n5 - Clinico Geral\nEscolha a especialidade do medico:");
						scanf("%d",esp);fflush(stdin);
					}
					if(esp==1){strcpy(m.especialidade,"Nutricionista");}
					if(esp==2){strcpy(m.especialidade,"Cardiologista");}
					if(esp==3){strcpy(m.especialidade,"Pediatra");}
					if(esp==4){strcpy(m.especialidade,"Neurologista");}
					if(esp==5){strcpy(m.especialidade,"Clinico Geral");}
					tamanho=strlen(m.especialidade);
					m.especialidade[tamanho+1]='\0';
                    break;
				case'5':
					printf("Digite o turno da consulta (0 - MANHA/1 - TARDE):");
					scanf("%d",&turno);fflush(stdin);
					while(turno>2 || turno<0){
						printf("Digite o turno da consulta (0 - MANHA/1 - TARDE):");
						scanf("%d",&turno);fflush(stdin);
					}
					if(turno==0){
						for(i=0;i<5;i++){
							printf("1 - Segunda\n2 - Terca\n3 - Quarta\n4 - Quinta\n5 - Sexta\n0 - Dias ja determinados.\n");
							scanf("%d",&turno);fflush(stdin);
							if(turno==0)
								break;
							else if(turno<6 && turno>0)
								m.tabela[0][turno-1]='X';
							else{
								printf("Digite um dia valido!\n");
								i--;
							}
						}
					}	
					else{
						for(i=0;i<5;i++){
							printf("1 - Segunda\n2 - Terca\n3 - Quarta\n4 - Quinta\n5 - Sexta\n0 - Dias ja determinados.\n");
							scanf("%d",&turno);fflush(stdin);
							if(turno==0)
								break;
							else if(turno<6 && turno>0)
								m.tabela[1][turno-1]='X';
							else{
								printf("Digite um dia valido!\n");
								i--;
							}
						}
					}
					break;
				case'0':
					break;
                default:printf("Opcao invalida!\n");
				}
			}while (op != '0');
            fseek(arq, -1 * (int)sizeof(Medico), 1);
            status = fwrite(&m, sizeof(Medico), 1, arq);
            if (status != 1)
                printf("Erro de gravacao!\n");
            else
                printf("Contato alterado com sucesso!\n");
		}
	}
}

void manutencao_medico(FILE *arqM, char nome[]){
	FILE *arq2;
	Medico c;
    char n[] = "copia";
    int pos;
    fseek(arqM, 0, 0);
    arq2 = criarArquivo(n);
    if (arq2 == NULL)
        printf("Impossivel realizar manutencao!\n");
    else {
        while (1) {
            pos = fread(&c, sizeof(Medico), 1, arqM);
            if (pos != 1) {
                if (!feof(arqM))
                    printf("Erro na leitura!\n");
                else
                    printf("Manutencao de medicos feita!\n");
                break;
            }
            else {
                if (c.status == 1) {
                    pos = fwrite(&c, sizeof(Medico), 1, arq2);
                    if (pos != 1) {
                        printf("Erro ao copiar!\n");
                    }
                }
            }
        }
        fclose(arqM);
        remove(nome);
        fclose(arq2);
        rename(n, nome);
        return;
    }
    fclose(arqM);
}

void montar_tree_medicos(FILE *arq, TNO **raiz){
	Medico aux;
    int pos, posicao;
    fseek(arq, 0, 0);
    while (1) {
        pos = fread(&aux, sizeof(Medico), 1, arq);
        if (pos != 1) {
            if (!feof(arq))
                printf("Erro na leitura!\n");
            break;
        }
        else{
            if(aux.status == 1){
                posicao = ftell(arq) / sizeof(Medico) - 1;
				insert(&(*raiz), aux.CRM, posicao);
            }
        }
    }
}

void exibir_medico(FILE * arq, TNO *indice, char crm[]) {
    Medico c;
    int pos, status;
    pos = buscar(indice, crm);
    if (pos == -1)
        printf("\nContato nao cadastrado!\n");
    else {
        fseek(arq, pos * sizeof(Medico), 0);
        status = fread(&c, sizeof(Medico), 1, arq);
        if (status != 1)
            printf("Erro de leitura!\n");
        else {
            printf("Nome: %s \n", c.nome);
			printf("Especialidade: %s", c.especialidade);
        }
    }
}
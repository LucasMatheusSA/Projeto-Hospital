//Main.c
#include "Types.h"
#include "Paciente.h"
#include "Validacoes.h"
#include "Tree.h"
#include "Medico.h"
#include "Consulta.h"


int main(){
    char op,op1,op2,op3, cpf[12], paciente[] = "arq_paciente.txt", medico[] = "arq_medico.txt", consulta[]="arq_consulta.txt", auxNome[T], crm[9], especi[50];
    int opp = 0, i = 0, pos = 0, esp, turnoX;
    FILE * arqP, *arqM, *arqCon;
    Paciente aux;
	Consulta auxCon;
    TNO *treeP =NULL, *treeM =NULL;
	Queue Fila;

    arqP = criarArquivo(paciente);//cria arquivo paciente
	arqM = criarArquivo(medico);//cria arquivo medico
	arqCon = criarArquivo(consulta);// cria arquivo consulta
    montar_tree_paciente(arqP, &treeP);//monta arvore paciente
	montar_tree_medicos(arqM, &treeM);//monta arvore medico
	manutencao_consulta(arqCon);
    do{
		system("cls");
		printf("--- MENU ---\n");
        printf("1 - Paciente\n2 - Medicos\n3 - Consultas\n0 - Sair\nDigite a opcao desejada: ");
        op = getchar(); fflush(stdin);
        switch(op){
        case'1':
            if(arqP == NULL)
                printf("Erro ao tentar criar ou abrir arquivo de pacientes!\n");
            else{
                do{
                    system("cls");
					printf("-->MENU PACIENTE\n\n");
                    printf("1 - Cadastrar paciente \n2 - alterar paciente  \n3 - Exibir paciente \n4 - Buscar por nome\n5 - Remover paciente \n0 - Voltar\nDigite a opcao:");
                    op1 = getchar(); fflush(stdin);
                    switch (op1){
                    case'1':
						printf("\nInforme o CPF:");
                        CPF(cpf);
                        opp = validar_cpf(cpf);
                        if (opp == 1)
                            cadastrar_paciente(arqP, &treeP, cpf);
                        else{
                            printf("\nCPF invalido!\n");
                        }
                        system("pause");
                        break;
                    case'2':
						printf("\nInforme o CPF:");
                        CPF(cpf);
                        opp = validar_cpf(cpf);
                        if (opp == 1) {
                            alterar_paciente(arqP, &treeP, cpf);
                        }
                        else {
                            printf("\nCPF invalido!\n");
                        }
                        system("pause");
                        break;
                    case'3':
						printf("\nInforme o CPF: ");
                        CPF(cpf);
                        opp = validar_cpf(cpf);
                        if (opp == 1) {
                            exibir(arqP, treeP, cpf);
                        }
                        else {
                            printf("CPF invalido!\n");
                        }
                        system("pause");
                        break;
                    case'4':
						NOME(auxNome);
                        opp = validar_nome(auxNome);
                        formata_nome(auxNome);
						fseek(arqP,0,0);
                        if (opp == 1) {
                            while (1){
                                pos = consultar_nome_paciente(arqP, auxNome, pos);
                                if (pos == -1) {
                                    printf("ERRO - Falha na leitura!\n");
                                    break;
                                }
                                else if (pos >= 0) {
                                    fseek(arqP, pos * sizeof(Paciente), 0);
                                    opp=fread(&aux, sizeof(Paciente), 1, arqP);
									if(opp!=0){
										if(aux.status==1){
											printf("Nome: %s \n", aux.nome);
											printf("Telefone: %s \n", aux.fone);
											printf("Email: %s \n", aux.email);
											pos=pos+1;
										}
									}
									else{
										printf("Resultados acima!\n");
										break;
									}
                                }
                                else{
                                    printf("Resultados acima!\n");
                                    break;
                                }
                            }
                        }
                        system("pause");
                        break;
                    case'5':
						printf("Informe o CPF: ");
                        CPF(cpf);
                        opp = validar_cpf(cpf);
                        if (opp == 1) {
							remover(arqP, &treeP, cpf,arqCon);
                        }
                        else {
                            printf("CPF invalido!\n");
                        }
                        system("pause");
                        break;
                    case'0':system("cls"); break;
                    default: printf("Opcao invalida!\n");break;
                    }
                }while (op1 != '0');
            }
            break;
        case'2':
			if(arqM == NULL)
                printf("Erro ao tentar criar ou abrir arquivo de medicos!\n");
            else{
				do{
					system("cls");
					printf("-->MENU MEDICO\n\n");
					printf("1 - Cadastrar medico \n2 - Procurar  por especialidade\n3 - Procurar  por nome\n4 - Remover  medico\n5 - alterar medico\n0 - Voltar \nDigite a opcao:");
					op2 = getchar(); fflush(stdin);
					switch(op2){
					case'1':
CRM(crm);
						opp=validar_crm(crm);
						if(opp==1){
							cadastrar_medico(arqM, &treeM, crm);
						}
						else
							printf("CRM invalido!\n");
						system("pause");
						break;
					case'2':
						printf("1 - Nutricionista\n2 - Cardiologista\n3 - Pediatra\n4 - Neurologista\n5 - Clinico Geral\nEscolha a especialidade: ");
						scanf("%d",&esp);fflush(stdin);
						while(esp>5 || esp<1){
							printf("\n\nOpcao invalida, escolha entre:\n");
							printf("1 - Nutricionista\n2 - Cardiologista\n3 - Pediatra\n4 - Neurologista\n5 - Clinico Geral\nEscolha a especialidade: ");
							scanf("%d",esp);fflush(stdin);
						}
						if(esp==1){strcpy(especi,"Nutricionista");}
						if(esp==2){strcpy(especi,"Cardiologista");}
						if(esp==3){strcpy(especi,"Pediatra");}
						if(esp==4){strcpy(especi,"Neurologista");}
						if(esp==5){strcpy(especi,"Clinico Geral");}
						especi[(strlen(especi))+1]='\0';
						busca_especialidade(arqM, especi);
						system("pause");
						break;
					case'3':
						NOME(auxNome);
                        opp = validar_nome(auxNome);
                        if(opp == 1){
							formata_nome(auxNome);
							consultar_nome_medico(arqM, auxNome);
						}
						else
							printf("Nome invalido!\n");
						system("pause");
						break;
					case'4':
						CRM(crm);
						opp=validar_crm(crm);
						if(opp==1){
							removerMed(arqM, &treeM, crm,arqCon);
						}
						else
							printf("CRM invalido!\n");
						system("pause");
						break;
					case'5':
						CRM(crm);
						opp=validar_crm(crm);
						if(opp==1){
							alterar_medico(arqM, &treeM, crm);
						}
						else
							printf("CRM invalido!\n");
						system("pause");
						break;
					case'0':
						system("cls");
						break;
					default:printf("Opcao invalida\n");break;
					}
				}while(op2!='0');
			}
            break;
        case'3':
			if(arqM == NULL)
				printf("Erro ao tentar criar ou abrir arquivo de medicos\n");
			else{
				do{
					system("cls");
					printf("-->MENU CONSULTA\n\n");
					printf("1 - Marcar Consulta\n2 - Consultar pacientes\n3 - Consultar consultas\n4 - Desmarcar consulta\n0 - Voltar\nEscolha a opcao:");
					op3=getchar();fflush(stdin);
					switch(op3){
					case'1':printf("\nInforme o CPF:");
                        CPF(cpf);
                        opp = validar_cpf(cpf);
                        if (opp == 1){
							opp = buscar(treeP, cpf);
							if(opp!=-1){
								CRM(crm);
								opp=validar_crm(crm);
								if(opp==1){
									opp = buscar(treeM, crm);
									if(opp!=-1){
										marcar_consulta(cpf,crm,arqM,arqCon,opp);
									}
									else
										printf("Medico nao cadastrado!\n");
								}
								else
									printf("CRM invalido!\n");
							}
							else
								printf("Paciente nao cadastrado!\n");
						}
						else
							printf("CPF invalido!\n");
						system("pause");
						break;
					case'2':
						CRM(crm);
						opp=validar_crm(crm);
						if(opp==1){
							strcpy(auxCon.crm,crm);
							opp = buscar(treeM, crm);
							if(opp!=-1){
								do{
									printf("Informe uma data valida:\n");
									printf("Dia: ");
									scanf("%d", &auxCon.dia); fflush(stdin);
									printf("Mes: ");
									scanf("%d", &auxCon.mes); fflush(stdin);
									printf("Ano: ");
									scanf("%d", &auxCon.ano); fflush(stdin);
									printf("Digite o turno:");scanf("%d",&turnoX);fflush(stdin);
									opp = validar_dia(auxCon.dia,auxCon.mes,auxCon.ano,turnoX);
								}while (opp == 0);
									Consultar_paciente(arqCon,crm,auxCon.dia,auxCon.mes,auxCon.ano,turnoX,arqP,treeP);
								}
								else
									printf("Data invalida!\n");
							}
							else
								printf("Medico nao cadastrado!\n");
						system("pause");
						break;
					case'3':
						printf("\nInforme o CPF:");
                        CPF(cpf);
                        opp = validar_cpf(cpf);
						if(opp==1){
							Consultar_consulta(arqCon,cpf,arqM,treeM);
							system("pause");
							break;
						}
						printf("CPF invalido!\n");
						system("pause");
						break;
					case'4':
						printf("\nInforme o CPF:");
                        CPF(cpf);
                        opp = validar_cpf(cpf);
						if(opp==1){
							opp = buscar(treeP, cpf);
							if(opp!=-1){
								CRM(crm);
								opp=validar_crm(crm);
								if(opp==1){
									opp = buscar(treeM, crm);
									if(opp!=-1){
										desmarcar_consulta(cpf,crm,arqCon);
									}
									else
										printf("\nCRM nao cadastrado!\n");
								}
								else
									printf("\nCRM invalido!\n");
							}
							else
								printf("\nCPF nao cadastrado!\n");
						}
						else
							printf("\nCPF invalido!\n");
						system("pause");
						break;
					case'0':system("cls");
						break;
					default:printf("Opcao invalida!\n");break;
					}
				}while(op3!='0');
			}
            break;
        case'0':
            break;
		default:printf("Opcao invalida!\n");break;
			}
	}while (op != '0');
    manutencao(arqP , paciente);//tratar arq paciente
	manutencao_medico(arqM, medico);//tratar arq medico 
	fclose(arqCon);
    system("pause");
    return 0;
}

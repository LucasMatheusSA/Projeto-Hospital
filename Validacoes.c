//Validacoes.c
#include "Types.h"

FILE *criarArquivo(char nome[]){
    FILE * arq;
    arq = fopen(nome, "r+b");
    if (arq == NULL){
        arq = fopen(nome, "w+b");
    }
    return arq;
}

int validar_nome(char nome[]) {
    int i, tamanho = strlen(nome);
    for (i = 0; i<tamanho; i++){
        if(isdigit(nome[i]) != 0 || iscntrl(nome[i]) != 0 || ispunct(nome[i]) != 0) {
            return 0;
        }
    }
    return 1;
}

void formata_nome(char nome[]) {
    int i, z, contSpace = 0, tamanho = strlen(nome);
    while (1) {
        if (isspace(nome[0]) != 0) {
            for (i = 0; i<tamanho; i++) {
                nome[i] = nome[i + 1];
            }
        }
        else
            break;
    }
    if (isalpha(nome[0]) != 0) {
        for (i = 0; i<tamanho; i++) {
            if (isalpha(nome[i]) != 0) {
                contSpace = 0;
                nome[i] = tolower(nome[i]);
            }
            else if (isspace(nome[i]) != 0) {
                contSpace++;
                if (contSpace>1) {
                    i--;
                    for (z = i; z<tamanho; z++) {
                        nome[z] = nome[z + 1];
                    }
                }
            }
        }
    }
    else{
        printf("Erro ao formatar o nome!\n");
		return;
	}
    nome[0] = toupper(nome[0]);
    for (i = 1; nome[i] != '\0'; i++) {
        if (isspace(nome[i - 1]) != 0)
            nome[i] = toupper(nome[i]);
    }
}

void NOME(char nome[]) {
    char aux;
    int i, x = 0;
    printf("\nDigite o nome:");
    for (i = 0; i == i; i++) {
        if (i<T - 1) {
            nome[i] = getche();fflush(stdin);
            if(nome[i] == 13){
                nome[i] = '\0';
                printf("\n");
                break;
            }
        }
        else{
            aux = getch();fflush(stdin);
            if (aux == 13) {
                nome[T - 1] = '\0';
                break;
            }
        }
    }
}

int validar_fone(char fone[]) {
    int i = 0, tamanho = strlen(fone);
	if(tamanho < 7 || tamanho > 15){
		return 0;
	}
    for (i = 0; i<tamanho - 1; i++) {
        if (isdigit(fone[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

void CPF(char cpf[]) {
    int i, ok = 0;
    char aux;
    for (i = 0; i == i; i++) {
        if(i<11){
            cpf[i] = getche();fflush(stdin);
            if (i == 2 || i == 5)
                printf(".");
            else if (i == 8)
                printf("-");
        }
        else if (i >= 11){
            i--;
            aux = getch();fflush(stdin);
            if (aux == 13)
                break;
        }
    }
    cpf[i+1] = '\0';
}

int validar_cpf(char cpf[]) {
    int i = 0, soma = 0, dig1 = 0, dig2 = 0, divisao = 0, tamanho = strlen(cpf);
    if (tamanho>11 || tamanho<11)
        return 0;
    for (i = 0; i<tamanho; i++) {
        if (isdigit(cpf[i]) == 0) {
            return 0;
        }
    }
	if ((strcmp(cpf, "00000000000") == 0) || 
		(strcmp(cpf, "11111111111") == 0) || (strcmp(cpf, "22222222222") == 0) || 
		(strcmp(cpf, "33333333333") == 0) || (strcmp(cpf, "44444444444") == 0) || 
		(strcmp(cpf, "55555555555") == 0) || (strcmp(cpf, "66666666666") == 0) || 
		(strcmp(cpf, "77777777777") == 0) || (strcmp(cpf, "88888888888") == 0) || 
		(strcmp(cpf, "99999999999") == 0))
		return 0;
    for (i = 0; i<11; i++)
        cpf[i] = cpf[i] - 48;
    
    for (i = 0; i<9; i++)
        soma = (cpf[i] * (10 - i)) + soma;
    divisao = soma % 11;
    if (divisao >= 2)
        dig1 = 11 - divisao;
    
    soma = 0;
    for (i = 0; i<10; i++)
        soma += cpf[i] * (11 - i);
    divisao = soma % 11;
    if (divisao >= 2)
        dig2 = 11 - divisao;
    if (dig1 == cpf[9] && dig2 == cpf[10]){
        for (i = 0; i<11; i++)
            cpf[i] = cpf[i] + 48;
        return 1;
    }
    else
        return 0;
}
int valiar_email(char email[]) {
    int cont = 0, i = 0, tamanho = strlen(email);
	if(email[0]=='@'){
		return 0;
	}
    if (isalpha(email[0] == 0) && email[i]!='@') {
        return 0;
    }
    for (i = 0; i<tamanho - 1; i++) {
        if (email[i] == '@') {
            cont = cont + 1;
            if (cont>1) {
                return 0;
            }
        }
    }
    if (cont == 0) {
        return 0;
    }
    return 1;
}

int dia_semana(Data d){
	switch (d.mes)
	{
	case 1: break;
	case 2: d.dia += 31; break;
	case 3: d.dia += 59; break;
	case 4: d.dia += 90; break;
	case 5: d.dia += 120; break;
	case 6: d.dia += 151; break;
	case 7: d.dia += 181; break;
	case 8: d.dia += 212; break;
	case 9: d.dia += 243; break;
	case 10: d.dia += 273; break;
	case 11: d.dia += 304; break;
	case 12: d.dia += 334; break;
	}
	if (((d.ano % 4) == 0) && (((d.ano % 100) != 0) || ((d.ano % 400) == 0)) && (d.mes > 2))
		d.dia += 1;
	d.dia += -1 + (d.ano - 1) * 365 + (d.ano - 1) / 4 - (d.ano - 1) / 100 + (d.ano - 1) / 400;

	switch (d.dia % 7)
	{
	case 0: return 0;
	case 1: return 1;
	case 2: return 2;
	case 3: return 3;
	case 4: return 4;
	}
	return 5;
}

int ano_(int ano) {
	if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0))
		return TRUE;
	else
		return FALSE;

}

int validar_data_(int dia, int mes, int ano) {
	if (ano > 0) {
		if (ano_(ano)) {
			if (mes >= 1 && mes <= 12) {
				if (mes == 1 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 2 && (dia <= 29 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 3 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 4 && (dia <= 30 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 5 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 6 && (dia <= 30 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 7 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 8 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 9 && (dia <= 30 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 10 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 11 && (dia <= 30 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 12 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				return FALSE;
			}
			return FALSE;
		}
		else {
			if (mes >= 1 && mes <= 12) {
				if (mes == 1 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 2 && (dia <= 28 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 3 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 4 && (dia <= 30 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 5 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 6 && (dia <= 30 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 7 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 8 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 9 && (dia <= 30 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 10 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 11 && (dia <= 30 && dia >= 1)) {
					return TRUE;
				}
				if (mes == 12 && (dia <= 31 && dia >= 1)) {
					return TRUE;
				}
				return FALSE;
			}
			return FALSE;
		}
	}
	return FALSE;
}
int validar_dia(int dia, int mes, int ano, int turno) {
	struct tm *agora;
	time_t data;
	Data hoje;
	data = time(NULL);
	agora = localtime(&data);
	hoje.dia = agora->tm_mday;
	hoje.mes = agora->tm_mon + 1;
	hoje.ano = agora->tm_year + 1900;
	if (hoje.ano > ano) {
		return 0;
	}
	else if (hoje.ano == ano) {
		if (hoje.mes > mes) {
			return 0;
		}
		else if (hoje.mes == mes) {
			if (hoje.dia > dia) {
				return 0;
			}
		}
	}
	if (dia_semana(hoje)<0 || dia_semana(hoje)>4)
		return FALSE;
	else
		return TRUE;
}


//Paciente.c
#include "Types.h"
#include "Validacoes.h"
#include "Tree.h"
#include "Consulta.h"

void cadastrar_paciente(FILE * arq, TNO **indice, char cpf[]) {
    Paciente c;
    int status, pos, local, opp = 0;
    char auxNome[T];
    fseek(arq, 0, 2);
    pos = buscar(*indice, cpf);
    if (pos == -1) {
        fseek(arq, 0, 2);
        strcpy(c.CPF, cpf);
        NOME(auxNome);
        opp = validar_nome(auxNome);
        while (opp == 0) {
            printf("Digite um nome valido: ");
            NOME(auxNome);
            opp = validar_nome(auxNome);
        }
        formata_nome(auxNome);
        strcpy(c.nome, auxNome);
        printf("Informe o telefone: ");
        fgets(c.fone, 16, stdin);
        opp = validar_fone(c.fone);
        while (opp == 0) {
            printf("Digite um telefone valido: ");
            fgets(c.fone, 16, stdin);
            opp = validar_fone(c.fone);
        }
        printf("Informe o e-mail: ");
        fgets(c.email, 100, stdin);
        opp = valiar_email(c.email);
        while (opp == 0) {
            printf("Digite um e-mail valido: ");
            fgets(c.email, 100, stdin);
            opp = valiar_email(c.email);
        }
        c.status = 1;
        status = fwrite(&c, sizeof(Paciente), 1, arq);
        if (status != 1)
            printf("Erro de gravacao!\n");
        else{
            local = ftell(arq) / sizeof(Paciente) - 1;
            insert(indice, cpf, local); 
            printf("Paciente cadastrado com sucesso!\n");
        }
    }
    else {
        printf("\nPaciente ja cadastrado!\n");
    }
}

void alterar_paciente(FILE * arq, TNO **indice, char cpf[]) {
    Paciente c;
    int pos, status, opp = 0;
    char auxNome[T], op;
    pos = buscar(*indice, cpf);
    if (pos == -1)
        printf("\nContato nao cadastrado!\n");
    else {
        fseek(arq, pos * sizeof(Paciente), 0);
        status = fread(&c, sizeof(Paciente), 1, arq);
        if (status != 1)
            printf("Erro de leitura!\n");
        else{
            do{
                system("cls");
				printf("Paciente encontrado!\n\n");
                printf("Nome: %s\nCPF: %s\nTelefone: %sE-mail: %s\n", c.nome, c.CPF, c.fone, c.email);
                printf("1 - alterar nome \n2 - alterar telefone \n3 - alterar email \n0 - Voltar \nDigite a opcao: ");
                op = getchar();fflush(stdin);
                switch (op){
                case'1':NOME(auxNome);
                    opp = validar_nome(auxNome);
                    while (opp == 0) {
                        printf("Nome invalido!\n");
                        NOME(auxNome);
                        opp = validar_nome(auxNome);
                    }
                    formata_nome(auxNome);
                    strcpy(c.nome, auxNome);
                    printf("Nome alterado com sucesso!\n");
                    system("pause");
                    break;
                case'2':printf("Informe o novo telefone: ");
                    fgets(c.fone, 16, stdin);
                    opp = validar_fone(c.fone);
                    while (opp == 0) {
                        printf("Digite um telefone valido: ");
                        fgets(c.fone, 100, stdin);
                        opp = validar_fone(c.fone);
                    }
                    printf("Telefone alterado com sucesso!\n");
                    system("pause");
                    break;
                case'3':printf("Informe o novo e-mail: ");
                    fgets(c.email, 100, stdin);
                    opp = valiar_email(c.email);
                    while(opp == 0){
                        printf("Digite um e-mail valido: ");
                        fgets(c.email, 100, stdin);
                        opp = valiar_email(c.email);
                    }
                    printf("E-mail alterado com sucesso!\n");
                    system("pause");
                    break;
                case'0':
                    break;
                default:printf("Opcao invalida!\n");
                }
            }while (op != '0');
            fseek(arq, -1 * (int)sizeof(Paciente), 1);
            status = fwrite(&c, sizeof(Paciente), 1, arq);
            if (status != 1)
                printf("Erro de gravacao!\n");
            else
                printf("Contato alterado com sucesso!\n");
        }
    }
}

void exibir(FILE * arq, TNO *indice, char cpf[]) {
    Paciente c;
    int pos, status;
    pos = buscar(indice, cpf);
    if (pos == -1)
        printf("\nContato nao cadastrado!\n");
    else {
        fseek(arq, pos * sizeof(Paciente), 0);
        status = fread(&c, sizeof(Paciente), 1, arq);
        if (status != 1)
            printf("Erro de leitura!\n");
        else {
            printf("\n\nNome: %s \n", c.nome);
            printf("Telefone: %s", c.fone);
            printf("Email: %s \n", c.email);
        }
    }
}

void remover(FILE * arq, TNO **indice, char cpf[],FILE *arq2){
    Paciente c;
    int pos, status;
    pos = buscar(*indice, cpf);
	if(busca_consulta_paciente(arq2,cpf)==TRUE){
		printf("\nPaciente nao pode ser removido pois esta marcado numa consulta!\n");return;
	}
    if(pos == -1){
        printf("\nContato nao cadastrado!\n");
    }
    else{
        fseek(arq, pos * sizeof(Paciente), 0);
        status = fread(&c, sizeof(Paciente), 1, arq);
        if(status != 1){
            printf("Erro de leitura!\n");
        }
        else{
            c.status = 0;
            fseek(arq, -1*sizeof(Paciente) , 1);
            status = fwrite(&c, sizeof(Paciente), 1, arq);
            if(status != 1){
                printf("Erro na remocao!\n");
            }
            else{
                printf("\nContato removido com sucesso!\n");
                removeTree(indice, cpf);
            }
        }
    }
}

int consultar_nome_paciente(FILE * arq, char nomeAux[], int pos) {
    Paciente c;
    int status, position;
    fseek(arq, pos * sizeof(Paciente), 0);
    while (1) {
        status = fread(&c, sizeof(Paciente), 1, arq);
        if (status != 1) {
            if (!feof(arq))
                return -1;
            return -2; 
        }
        else {
            if (strcmp(nomeAux, c.nome) == 0 && c.status == 1) {
                position = ftell(arq) / sizeof(Paciente) - 1;
                return position;
            }
        }
    }
}

void manutencao(FILE *arq, char nome[]) {
    FILE *arq2;
    Paciente c;
    char n[] = "copia";
    int pos;
    fseek(arq, 0, 0);
    arq2 = criarArquivo(n);
    if (arq2 == NULL)
        printf("Impossivel realizar manutencao!\n");
    else {
        while (1) {
            pos = fread(&c, sizeof(Paciente), 1, arq);
            if (pos != 1) {
                if (!feof(arq))
                    printf("Erro na leitura!\n");
                else
                    printf("Manutencao de pacientes feita!\n");
                break;
            }
            else {
                if (c.status == 1) {
                    pos = fwrite(&c, sizeof(Paciente), 1, arq2);
                    if (pos != 1) {
                        printf("Erro ao copiar!\n");
                    }
                }
            }
        }
        fclose(arq);
        remove(nome);
        fclose(arq2);
        rename(n, nome);
        return;
    }
    fclose(arq);
}

void montar_tree_paciente(FILE *arq, TNO **raiz){
    Paciente aux;
    int pos, posicao;
    fseek(arq, 0, 0);
    while (1) {
        pos = fread(&aux, sizeof(Paciente), 1, arq);
        if (pos != 1) {
            if (!feof(arq))
                printf("Erro na leitura!\n");
            break;
        }
        else{
            if(aux.status == 1){
                posicao = ftell(arq) / sizeof(Paciente) - 1;
                insert(&(*raiz), aux.CPF, posicao);
            }
        }
    }
}
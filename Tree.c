//Tree.c
#include "Types.h"
 
void insert(TNO **raiz, char cpf[], int posicao) {
    if (*raiz == NULL) {
        *raiz = (TNO *)malloc(sizeof(TNO));
        strcpy((*raiz)->cpfORcrm, cpf);
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        (*raiz)->pos = posicao;
        (*raiz)->status = 1;
    }
    else if (strcmp(cpf, (*raiz)->cpfORcrm) < 0)
        insert(&((*raiz)->esq), cpf, posicao);
    else
        insert(&((*raiz)->dir), cpf, posicao);
}
 
void emOrdem(TNO * raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%i \n", raiz->cpfORcrm);
        emOrdem(raiz->dir);
    }
}
 
TNO * maior(TNO **raiz) {
    TNO * aux;
    aux = *raiz;
    if (aux->dir == NULL) {
        *raiz = (*raiz)->esq;
        return aux;
    }
    else
        return maior(&((*raiz)->dir));
}
 
void remover_no(TNO **raiz) {
    TNO * pos=*raiz;
    if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) 
        *raiz = NULL;
    else if ((*raiz)->esq == NULL) 
        *raiz = (*raiz)->dir;
    else if ((*raiz)->dir == NULL) 
        *raiz = (*raiz)->esq;
    else { 
        pos = maior(&((*raiz)->esq));
        strcpy((*raiz)->cpfORcrm, pos->cpfORcrm);
        (*raiz)->pos = pos->pos;
    }
    free(pos);
}
 
void removeTree(TNO **raiz, char elem[]) {
    int result;
    if (*raiz == NULL)
        printf("Elemento não encontrado!\n");
    else {
        result = strcmp(elem, (*raiz)->cpfORcrm);
        if (result == 0)
            remover_no(&(*raiz));
        else if (result < 0)
            removeTree(&(*raiz)->esq, elem);
        else
            removeTree(&(*raiz)->dir, elem);
    }
}

TNO * buscar_no(TNO *raiz, char cpfOUcrm[]) {
    if(raiz == NULL)
        return NULL;
    else{
        if(strcmp(cpfOUcrm, raiz->cpfORcrm) == 0){
            return raiz;
		}
        else if(strcmp(raiz->cpfORcrm, cpfOUcrm) > 0)
            return buscar_no(raiz->esq, cpfOUcrm);
        else
            return buscar_no(raiz->dir, cpfOUcrm);
    }
}
 
int buscar(TNO *indice, char cpfOUcrm[]) {
    TNO * result;
    result = buscar_no(indice, cpfOUcrm);
    if (result == NULL)
        return -1;
    else
        return result->pos;
}
 
TNO *destroy(TNO **raiz) {
    if (raiz != NULL) {
        destroy(&(*raiz)->esq);
        destroy(&(*raiz)->dir);
        free(raiz);
    }
    return NULL;
}
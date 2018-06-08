//Tree.h
#include "Types.h"
 
void emOrdem(TNO * raiz);// imprime codigos da arvore em ordem 
void insert(TNO **raiz, char cpf[], int posicao);// inseri no na arvore  
TNO * buscar_no(TNO *raiz, char nome[]);// retorna no
int buscar(TNO *indice, char cpf[]);// retorn pos
void removeTree(TNO **raiz, char nome[]);// remove no
void remover_no(TNO **raiz);
TNO * maior(TNO **raiz);
TNO *destroy(TNO **raiz);// destroi arvore
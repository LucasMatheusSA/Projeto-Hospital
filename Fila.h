//Fila.h
#include "Types.h"

void createQueue(Queue * fila);//Cria fila
void enQueue(Queue * fila, Consulta valor);//coloca struct de espera na fila 
Consulta deQueue(Queue * fila);//tira struct de espera da fila 
Consulta head(Queue fila);// mostra a primeira struct de espera da fila 
int isEmpty(Queue fila);// checa se a fila esta fazia 
int isFull(Queue fila);// checa se a fila esta cheia 
void destroyQueue(Queue * fila);// destroi fila 

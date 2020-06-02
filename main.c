#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Graph/graph.h"
#include "List/list.h"
#include "User/user.h"
#define MAX 6

int main(){
     char cities[7][50] = {"napoli","milano","berlino","roma","palermo","londra","Catania"};
    /*vedere di risolvere con un numero superiore ai nodi, per ora il numero deve essere = ai nodi
     for(int i=0;i<g->nodes_count;i++) {
        printf("valore di i=%d -- nodi = %d\n",i,g->nodes_count);
        setNodeName(g, i, cities[i]);
    }*/


    Graph g = initGraph(7); //allochiamo le variabili del grafo
    printf("\n\nil grafo e' %d\n\n\n\n",isEmpty(g));
    g = setGraph(g); //assegnamo i vertici
    printf("\n\nil grafo e' %d\n\n\n\n",isEmpty(g));

    addEdge(g,0,1,10,100); //(GRAFO,NODO ORIGINE, NODO DESTINAZIONE, PREZZO ARCO, KM );
    addEdge(g,0,3,1,100);
    addEdge(g,1,2,1,100);
    addEdge(g,3,0,1,100);
    addEdge(g,3,2,1,100);
    addEdge(g,3,4,1,100);
    addEdge(g,4,2,1,100);
    addEdge(g,2,5,1,100);
    printGraph(g);
    //puts("aggiunta nodo");
    //addNode(g);

   for(int i=0;i<g->nodes_count;i++) {
        printf("valore di i=%d -- nodi = %d\n",i,g->nodes_count);
        setNodeName(g, i, cities[i]);
    }

    printGraphWithNames(g);

    for(int i=0;i<g->nodes_count;i++) {
        printf("punteggio di %d = %d \n",i,g->infoVertex[i].cityPopularPoints);
    }


    addEdge(g,6,0,1,1);
    removeNode(g,3);
    //printf("pos 0 %s",g->infoVertex[0].name);


    printGraphWithNames(g);



    //ora devo aggiungere i vertici ed il nome corrispondente



    removeEdge(g,0,1);
    printGraph(g);

    puts("\n\n\n");
    removeNode(g,1);
    printGraph(g);
    printGraphWithNames(g);
    printf("Hello, World!\n");
return 0;
}

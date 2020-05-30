#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Graph/graph.h"
#include "List/list.h"
#define MAX 50

int main() {


    char cities[50][MAX] = {"napoli","milano","berlino","roma","palermo","londra","Catania"};


    Graph g = initGraph(6); //allochiamo le variabili del grafo
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
    //addNode(g);
    //addNode(g);

    for(int i=0;i<g->nodes_count;i++) {
        setNameVertexInVector(g, i, cities[i]);
    }

    for(int i=0;i<g->nodes_count;i++) {
        printf("punteggio di %d = %d \n",i,g->cityPoints[i]);
    }


    addEdge(g,6,0,1,1);
    removeNode(g,3);
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


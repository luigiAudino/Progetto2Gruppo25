#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Graph/graph.h"
#include "List/list.h"

int main() {


    Graph g = initGraph(6); //allochiamo le variabili del grafo
    printf("\n\nil grafo e' %d\n\n\n\n",isEmpty(g));
    g = setGraph(g); //assegnamo i vertici
    printf("\n\nil grafo e' %d\n\n\n\n",isEmpty(g));

    char* arr = malloc(50*sizeof(char));


    addEdge(g,0,1,10,100);
    addEdge(g,0,3,1,100);
    addEdge(g,1,2,1,100);
    addEdge(g,3,0,1,100);
    addEdge(g,3,2,1,100);
    addEdge(g,3,4,1,100);
    addEdge(g,4,2,1,100);
    addEdge(g,2,5,1,100);
    printGraph(g);


    setNameVertexInVector(g,0,"napoli");
    setNameVertexInVector(g,1,"milano");
    setNameVertexInVector(g,2,"berlino");
    setNameVertexInVector(g,3,"roma");
    setNameVertexInVector(g,4,"palermo");
    setNameVertexInVector(g,5,"londra");

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


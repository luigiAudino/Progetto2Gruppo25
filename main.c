#include <stdio.h>
#include "Graph/graph.h"
#include "List/list.h"

int main() {


    Graph g = initGraph(6); //allochiamo le variabili del grafo
    printf("\n\nil grafo e' %d\n\n\n\n",isEmpty(g));
    g = setGraph(g); //assegnamo i vertici
    printf("\n\nil grafo e' %d\n\n\n\n",isEmpty(g));


    addEdge(g,0,1,10,100);
    addEdge(g,0,3,1,100);
    addEdge(g,1,2,1,100);
    addEdge(g,3,0,1,100);
    addEdge(g,3,2,1,100);
    addEdge(g,3,4,1,100);
    addEdge(g,4,2,1,100);
    addEdge(g,2,5,1,100);
    printGraph(g);


    setNameVertex(g,0,"napoli");
    setNameVertex(g,1,"milano");
    setNameVertex(g,2,"berlino");
    setNameVertex(g,3,"roma");
    setNameVertex(g,4,"palermo");
    setNameVertex(g,5,"londra");

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


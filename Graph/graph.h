#ifndef Graph_Graph_h
#define Graph_Graph_h
#include "../List/list.h"

struct vertex{
    int key;
    char name[50];
    int cityPopularPoints;
    //cose di dijkstra
};
typedef struct vertex Vertex;

struct TGraph {
    //int* cityPopularPoints; //vettore dei punteggi per la meta 'gettonata' associati ad ogni nodo
    //char** vectorNames; //vettore dei nomi dei vertici parallelo al vettore di vertici
    int nodes_count;
    Vertex* infoVertex; //info su ogni vertice appartenente al grafo
    List *adj; //vettore di vertici
};


typedef struct TGraph* Graph;


Graph initGraph(int nodes_count);// Inizializza un nuovo grafo vuoto specificando in ingresso quanti nodi ci saranno nel grafo ed in contemporanea il vettore dei nomi delle città associate ai nodi

Graph setGraph(Graph G); //inizializza null i puntatori del vettore delle liste d'adiacenza e del vettore parallelo che contiene i nomi dei vertici

void freeGraph(Graph G); // Dealloca l'intero grafo

void printGraph(Graph G);// Stampa il grafo



/*funzioni del vettore di nomi*/
void removeNameFromVector(Graph G,int n); //rimuove il nome di un vertice dal vettore
void setNameVertexInVector(Graph G,int nVertex, char name[]); //associa il nome al vertice dato in ingresso
void printGraphWithNames(Graph G);// stampa il grafo coi nomi associati ai vertici numerici






/*funzioni degli archi*/

List removeEdge(Graph G, int source, int target);// Rimuove un arco specificando sorgente e target,restituisce la lista degli archi modifcata

void addEdge(Graph G, int source, int target, int price, int km); // Aggiunge al grafo G un arco da sorgente a target con prezzo 'price' e km 'km

int containsEdge(Graph G, int vertice1, int vertice2); // ritorna 1 se l'arco formato dai 2 vertici è contenuto nel grafo

int existVertici(Graph G, int v1,int v2); //Ritorna 1 se i due vertici sono compresi tra i vertici del grafo, 0 altr.
/*-----------------------------------*/

int isEmpty(Graph G); //ritorna 1 se il grafo e' VUOTO quindi punta a NULL, 0 altrimenti








// Aggiungi un nodo
void addNode(Graph G);

// Rimuovi un nodo dal grafo, sistemando gli indici e riallocando la memoria,E RIMUOVE ANCHE IL NOME ASSOCIATO AD ESSO NEL VETTORE DI NOMI
void removeNode(Graph G, int node_to_remove);

List checkListRemoval(List L, int node_to_remove);//rimuove il nodo contentente l'intero 'node_to_remove' dalla lista L e restituisce il puntatore alla lista

/*
// Crea un nuovo grafo e lo popola in base alla scelta effettuata dal menu
Graph graphCreationMenu(int n);

// Menu per la modifica e gestione dei grafi
void graphEditorMenu(Graph);*/

#endif

#ifndef Graph_Graph_h
#define Graph_Graph_h
#include "stdbool.h"
#include "../List/list.h"
#include"../Queue/queue.h"
#include"../Booking/booking.h"

/*Gruppo 25 - Progetto 2 - Giuliano Galloppi N86001508; Piero Junior Gaetani N86002210; Luigi Audino N86001513*/

struct vertex{
    int key;
    char name[50];
    int cityPopularPoints;
    int d; // == d[v] distanza del vertice v dal vertice sorgente nell'algoritmo di dijkstra
    int pi; // == pi[v] predecessore del vertice
};
typedef struct vertex Vertex;


struct TGraph {
    int nodes_count;
    Vertex* infoVertex; //Vettore di vertici il quale contiene info su ogni vertice appartenente al grafo
    List *adj;
};


typedef struct TGraph* Graph;

Graph presetGraph(Graph G);//Inizializzazione del grafo pre-settato con 20 mete e tratte

Graph initGraph(int nodes_count);// Inizializza un nuovo grafo vuoto specificando in ingresso quanti nodi ci saranno nel grafo ed in contemporanea il vettore dei nomi delle città associate ai nodi

void freeGraph(Graph G); // Dealloca l'intero grafo

void printGraph(Graph G);// Stampa il grafo

int isEmpty(Graph G); //ritorna 1 se il grafo e' VUOTO quindi punta a NULL, 0 altrimenti

/*FUNZIONI DIJKSTRA*/
int getFlyCost(Graph G,int s, int t);//Ritorna il costo totale del volo in base al percorso di cui sara' composto (calcolato da dijkstra in precedenza)

City getSP(Graph G,int s, int t);//Ritorna una Lista di citta' che contiene il percorso piu' breve da 's' a 't' calcolato da dijkstra in precedenza

void dijkstraCheaper(Graph G,int s); //[TRATTA PIU' ECONOMICA] Calcolo della tratta piu' economica con l'algoritmo di dijkstra
void dijkstraShortestDistance(Graph G,int s); //[TRATTA PIU' BREVE] Calcolo della tratta piu' breve con l'algoritmo di dijkstra

int extractMinDijkstra(Graph G,Queue Q);//Estrae il vertice col minimo d[] tra i vertici del grafo G , i quali sono contenuti nella coda di priorita' Q;

void relaxPrice(Graph G, int u, int v);//Rilassa l'arco (u,v) usando come peso il prezzo dell'arco; u = vertice attuale, v = vertice da raggiungere da u
void relaxKm(Graph G, int u, int v); //Rilassa l'arco (u,v) usando come peso i km dell'arco; u = vertice attuale, v = vertice da raggiungere da u

void printSP(Graph G,int s, int t);//Stampa il percorso a ritroso dal vertice target 't', al vertice sorgente 's'
/*FINE FUNZIONI DIJKSTRA*/


int destinationCheaper(Graph G, int nodeDeparture);//[META PIU' ECONOMICA]Ritorna la citta' meta/nodo piu' economica per la citta' di partenza/nodo inserita

int destinationMostPopular(Graph G, int nodeDepartureCity);//[META PIU' GETTONATA]Ritorna la citta' meta/nodo piu' gettonata per la citta' di partenza/nodo inserita

void printNodeLinks(Graph G, int node);//Stampa tutti i nodi con cui e' collegato/ha una tratta il nodo in ingresso
int existLinkDfs(Graph G,int v1,int v2);//Utilizza la visita in DFS. Ritorna 1 se e' possibile raggiungere un vertice v2 partendo da v1 pur passando da altri vertici (quindi nelle loro liste d'adiacenza)
void existLinkDfs1(Graph G, int i, int* aux,int verticeDiDestinazione,int* val);
int listContainsVertex(Graph G,int v1,int v2);//Restituisce 1 se nella lista d'adiacenza del vertice v1 e' presente un nodo che ha come target=v2, 0 altrimenti

/*Funzioni infoVertex*/
void addInfoVertex(Graph G); //Aggiunge una cella al vettore di informazioni sul vertice
void removeInfoVertex(Graph G,int n); //Rimuove le informazioni di un vertice
void printGraphInfoVertex(Graph G);//Stampa il vettore con tutte le informazioni dei vertici del grafo

void setNodeName(Graph G,int nVertex, char name[]); //associa il nome al vertice dato in ingresso
char* getNodeName(Graph G,int nVertex);//Ritorna il nome del nodo(vertice/citta') dato in input
int getNodeFromName(Graph G,char name[]);//Ritorna il corrispettivo numerico del nodo(vertice/citta') dato in input come nome
void printGraphOnlyWithNames(Graph G);//Stampa il grafo solo coi nominativi dei vertici
void printGraphIndexNameAndPoints(Graph G);// Stampa il grafo con gli indici relativi ed i nomi delle citta' presenti con il punteggio di gettonamento associato

void setNodeCityPopularPoints(Graph G,int nVertex,int points);//Assegna i punti 'gettonati' al nodo(vertice/citta') dato in input
int getNodeCityPopularPoints(Graph G, int nVertex);//Ritorna i punti 'gettonati' del nodo(vertice/citta') dato in input
void printCityPopularPoints(Graph G);//Stampa tutti i nodi/citta' coi punteggi gettonati associati

void printGraphWithNames(Graph G);// stampa il grafo completo coi nomi associati ai vertici numerici

City getAllCityFromGraph(Graph G);//Restituisce una lista di city con tutte le citta' del grafo

/*Funzioni degli archi*/
void setKm(Graph G, int v1, int v2,int km);//Assegna il peso 'km' all'arco (v1,v2) appartenente al grafo G, 0 altrimenti

int getKm(Graph G, int v1, int v2);//Restituisce i km dell'arco (v1,v2) appartenente al grafo G, 0 altrimenti

void setPrice(Graph G, int v1, int v2,int price);//Assegna il peso 'price' all'arco (v1,v2) appartenente al grafo G, 0 altrimenti

int getPrice(Graph G, int v1, int v2);//Restituisce il peso dell'arco (v1,v2) appartenente al grafo G, 0 altrimenti

List removeEdge(Graph G, int source, int target);// Rimuove un arco specificando sorgente e target,restituisce la lista degli archi modifcata

void addEdgeWithoutPrints(Graph G, int source, int target, int price, int km);//Aggiunge un arco al grafo coi rispettivi controlli senza stampe
void addEdge(Graph G, int source, int target, int price, int km); // Aggiunge al grafo G un arco da sorgente a target con prezzo 'price' e km 'km

int containsEdge(Graph G, int vertice1, int vertice2); //Ritorna 1 se l'arco(vertice1,vertice2) e' presente(contenuto) nel grafo, 0 altrimenti, e controlla che i vertici appartengano al grafo

bool existVertici(Graph G, int v1,int v2); //Ritorna 1 se i due vertici sono compresi tra i vertici del grafo, 0 altr.

/*Funzioni dei nodi/vertici*/
void addNode(Graph G);// Aggiunge un nodo al grafo, e richiama addInfoVertex che aggiunge una posizione al vettore di informazioni associate al nuovo nodo

void removeNode(Graph G, int node_to_remove);// Rimuove un nodo dal grafo, sistemando gli indici e riallocando la memoria,e richiama removeInfoVertex per rimuovere le info del nodo rimosso

List checkListRemoval(List L, int node_to_remove);//Rimuove il nodo contentente l'intero 'node_to_remove' dalla lista L e restituisce il puntatore alla lista

int getKeyVertexFromGraph(Graph g, City city);


//Punto 1 traccia progetto
ListUserBooking bookingCheaperOrShortestPath(Graph g, int departureKey, int destinationKey, ListUserBooking listUserBooking, User user);

int summaryPurchase(int priceOfPurchase, char departureName [], char destinationName [], User user);

#endif

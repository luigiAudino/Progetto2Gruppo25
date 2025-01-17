#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include "../Util/util.h"
#include "graph.h"
#include "../Input/inputReader.h"
#include <limits.h>

/*Gruppo 25 - Progetto 2 - Giuliano Galloppi N86001508; Piero Junior Gaetani N86002210; Luigi Audino N86001513*/

//#define EDGE_SUCC 0.33 //indica la percentuale di successo di creazione di un arco

//Inizializzazione del grafo pre-settato con 20 mete e tratte
Graph presetGraph(Graph G) {
    G = initGraph(20);

    //0 Napoli
    addEdgeWithoutPrints(G, 0, 1, 43, 775);
    addEdgeWithoutPrints(G, 0, 2, 71, 230);
    //1 Milano
    addEdgeWithoutPrints(G, 1, 3, 87, 1034);
    //2 Roma
    addEdgeWithoutPrints(G, 2, 0, 163, 230);
    addEdgeWithoutPrints(G, 2, 3, 84, 573);
    addEdgeWithoutPrints(G, 2, 4, 44, 922);
    addEdgeWithoutPrints(G, 2, 6, 157, 595);
    //3 Berlino
    addEdgeWithoutPrints(G, 3, 5, 46, 1095);
    //4 Palermo
    addEdgeWithoutPrints(G, 4, 3, 84, 573);
    //5 Londra
    //non ha archi uscenti
    //6 Cagliari
    addEdgeWithoutPrints(G, 6, 4, 112, 464);
    addEdgeWithoutPrints(G, 6, 7, 55, 934);
    addEdgeWithoutPrints(G, 6, 8, 74, 913);
    //7 Torino
    addEdgeWithoutPrints(G, 7, 4, 103, 1585);
    addEdgeWithoutPrints(G, 7, 8, 108, 401);
    //8 Venezia
    addEdgeWithoutPrints(G, 8, 9, 195, 153);
    addEdgeWithoutPrints(G, 8, 10, 102, 1345);
    //9 Bologna
    addEdgeWithoutPrints(G, 9, 10, 128, 1300);
    //10 Amsterdam
    addEdgeWithoutPrints(G, 10, 8, 253, 1345);
    addEdgeWithoutPrints(G, 10, 11, 121, 1540);
    addEdgeWithoutPrints(G, 10, 13, 125, 1404);
    //11 Barcellona
    addEdgeWithoutPrints(G, 11, 12, 40, 621);
    addEdgeWithoutPrints(G, 11, 19, 49, 1038);
    //12 Madrid
    addEdgeWithoutPrints(G, 12, 11, 40, 621);
    //13 Budapest
    addEdgeWithoutPrints(G, 13, 14, 154, 1352);
    //14 Corfu'
    addEdgeWithoutPrints(G, 14, 12, 286, 2734);
    addEdgeWithoutPrints(G, 14, 16, 162, 3287);
    //15 Ibiza
    addEdgeWithoutPrints(G, 15, 13, 172, 2441);
    addEdgeWithoutPrints(G, 15, 16, 153, 1089);
    addEdgeWithoutPrints(G, 15, 17, 143, 3298);
    //16 Lisbona
    //non ha archi uscenti
    //17 Mykonos
    addEdgeWithoutPrints(G, 17, 18, 249, 2147);
    //18 Praga
    //Non ha archi uscenti
    //19 Parigi
    addEdgeWithoutPrints(G, 19, 12, 67, 1275);

    //Settaggio dei nomi
    setNodeName(G, 0, "Napoli");
    setNodeName(G, 1, "Milano");
    setNodeName(G, 2, "Roma");
    setNodeName(G, 3, "Berlino");
    setNodeName(G, 4, "Palermo");
    setNodeName(G, 5, "Londra");
    setNodeName(G, 6, "Cagliari");
    setNodeName(G, 7, "Torino");
    setNodeName(G, 8, "Venezia");
    setNodeName(G, 9, "Bologna");
    setNodeName(G, 10, "Amsterdam");
    setNodeName(G, 11, "Barcellona");
    setNodeName(G, 12, "Madrid");
    setNodeName(G, 13, "Budapest");
    setNodeName(G, 14, "Corfu'");
    setNodeName(G, 15, "Ibiza");
    setNodeName(G, 16, "Lisbona");
    setNodeName(G, 17, "Mykonos");
    setNodeName(G, 18, "Praga");
    setNodeName(G, 19, "Parigi");

    //Settaggio punteggio di 'citta' gettonata' ad ogni citta'/nodo
    int points = 100;
    for (int i = 0; i < G->nodes_count; i++) {
        setNodeCityPopularPoints(G, i, points);
    }

    //Settaggio citta' piu' gettonate
    setNodeCityPopularPoints(G, 1, 250);
    setNodeCityPopularPoints(G, 10, 500);
    setNodeCityPopularPoints(G, 15, 700);
    setNodeCityPopularPoints(G, 17, 650);


    return G;
}

Graph initGraph(int nodes_count) {//Crea un grafo vuoto
    Graph G = (Graph) malloc(sizeof(struct TGraph));
    if (G == NULL) {
        puts("Impossibile allocare memoria per il grafo.\n");
    } else {
        G->adj = (List *) calloc(nodes_count, sizeof(List));
        if (G->adj == NULL) {
            puts("ERRORE: impossibile allocare memoria per il vettore di liste d'adiacenze");
            free(G);
            G = NULL;
        } else {
            G->infoVertex = (Vertex *) calloc(nodes_count, sizeof(struct vertex));
            G->nodes_count = nodes_count;

            for (int i = 0; i < G->nodes_count; i++) {
                G->adj[i] = NULL;  //Inizializzo i puntatori di puntatori facendoli puntare a NULL
                G->infoVertex[i].cityPopularPoints = 0; //Inizializzo i punteggi gettonati per le citta'
                G->infoVertex[i].key = i; //Memorizzo il corrispondente numerico del nodo
            }
        }
    }
    return G;
}

void freeGraph(Graph G) {
    if (G != NULL) {
        if (G->nodes_count > 0) {
            int i = 0;
            for (i = 0; i < G->nodes_count; i++) {
                freeList(G->adj[i]);
            }
        }
        free(G);
    }
}

void printGraphAux(Graph G) {
    if (G != NULL) {
        int x = 0;
        for (x = 0; x < G->nodes_count; x++) {
            printf("%d -> ", x);
            printList(G->adj[x]);
            printf("\n");
        }
    }
}

void printGraph(Graph G) {
    printGraphAux(G);
    printf("\n\n");
}


int isEmpty(Graph G) { // Se il puntatore al grafo e' NULL, quindi il grafo e' VUOTO (non e' allocato nulla) restituisce 1, 0 altrimenti
    return (G == NULL);
}


/*FUNZIONI DIJKSTRA*/
int getFlyCost(Graph G, int s, int t) {//Ritorna il costo totale del volo in base al percorso di cui sara' composto (calcolato da dijkstra in precedenza)
    int cost = 0;

    if (s != t) {
        cost = getPrice(G, G->infoVertex[t].pi, t);
        cost = cost + getFlyCost(G, s, G->infoVertex[t].pi);
    }
    return cost;
}

City getSP(Graph G, int s, int t) {//Ritorna una Lista di citta' che contiene il percorso piu' breve da 's' a 't' calcolato da dijkstra in precedenza

    City inizioPercorso = NULL;

    if (s != t) {
        inizioPercorso = getSP(G, s, G->infoVertex[t].pi);
    }

    inizioPercorso = enqueueCity(inizioPercorso, G->infoVertex[t].name);

    return inizioPercorso;
}


void dijkstraCheaper(Graph G, int s) {//[TRATTA PIU' ECONOMICA] Calcolo della tratta piu' economica con l'algoritmo di dijkstra

    Queue S = initQueue();
    Queue Q = initQueue();
    int min; //vertice minimo estratto dalla coda Q

    for (int i = 0; i < G->nodes_count; i++) {
        enqueue(Q, i);
        G->infoVertex[i].d = (INT_MAX / 2);
        G->infoVertex[i].pi = -1;
    }
    G->infoVertex[s].d = 0;
    G->infoVertex[s].pi = s;

    while (!emptyQueue(Q)) {

        min = extractMinDijkstra(G, Q);
        enqueue(S, min);

        List e = G->adj[min];
        while (e != NULL) {
            relaxPrice(G, min, e->target);
            e = e->next;
        }
    }

}

void dijkstraShortestDistance(Graph G, int s) {//[TRATTA PIU' BREVE] Calcolo della tratta piu' breve con l'algoritmo di dijkstra
    Queue S = initQueue();
    Queue Q = initQueue();
    int min; //vertice minimo estratto dalla coda Q

    for (int i = 0; i < G->nodes_count; i++) {
        enqueue(Q, i);
        G->infoVertex[i].d = (INT_MAX / 2);
        G->infoVertex[i].pi = -1;
    }
    G->infoVertex[s].d = 0;
    G->infoVertex[s].pi = s;

    while (!emptyQueue(Q)) {

        min = extractMinDijkstra(G, Q);
        enqueue(S, min);

        List e = G->adj[min];
        while (e != NULL) {
            relaxKm(G, min, e->target);
            e = e->next;
        }
    }

}


int extractMinDijkstra(Graph G, Queue Q) {//Estrae il vertice col minimo d[] tra i vertici del grafo G , i quali sono contenuti nella coda di priorita' Q
    Queue copia = initQueue();
    int min;
    int val;
    int temp;
    if (!emptyQueue(Q)) {
        min = dequeue(Q);
        enqueue(copia, min);
        while (!emptyQueue(Q)) {
            val = dequeue(Q);
            if (G->infoVertex[min].d > G->infoVertex[val].d) {
                enqueue(copia, val);
                min = val;
            } else {
                enqueue(copia, val);
            }
        }

        while (!emptyQueue(copia)) {//ricopio nella coda originale i valori tranne il minimo
            temp = dequeue(copia);
            if (temp != min) {
                enqueue(Q, temp);
            }
        }
    }

    return min;
}


//Funzioni relax
//G->infoVertex[v].d = d[v] ; G->infoVertex[v].pi = pi[v]
void relaxPrice(Graph G, int u,int v) {//Rilassa l'arco (u,v) usando come peso il prezzo dell'arco; u = vertice attuale, v = vertice da raggiungere da u
    if (!isEmpty(G)) {
        if (containsEdge(G, u, v) == 1) {
            int pesoArco = getPrice(G, u, v);
            if (G->infoVertex[v].d > ((G->infoVertex[u].d) + pesoArco)) {
                G->infoVertex[v].d = G->infoVertex[u].d + pesoArco; //distanza di v = dis U + peso (u,v)
                G->infoVertex[v].pi = u; // precedente di v = u
            }
        } else {
            printf("L'arco non e' contenuto nel grafo.");
        }
    }
}

void relaxKm(Graph G, int u, int v) {//Rilassa l'arco (u,v) usando come peso i km dell'arco; u = vertice attuale, v = vertice da raggiungere da u
    if (!isEmpty(G)) {
        if (containsEdge(G, u, v) == 1) {
            int pesoArco = getKm(G, u, v);
            if (G->infoVertex[v].d > ((G->infoVertex[u].d) + pesoArco)) {
                G->infoVertex[v].d = G->infoVertex[u].d + pesoArco; //distanza di v = dis U + peso (u,v)
                G->infoVertex[v].pi = u; // precedente di v = u
            }
        } else {
            printf("L'arco non e' contenuto nel grafo.");
        }
    }
}


//Stampa il percorso a ritroso dal vertice target 't', al vertice sorgente 's'
void printSP(Graph G, int s, int t) {
    printf("\ns = %d, t=%d\n", s, t);
    if (s != t) {
        printSP(G, s, G->infoVertex[t].pi);
        printf("PREDECESSORE DI %d = %d,", t, G->infoVertex[t].pi);
    } else {
        printf("PREDECESSORE DI %d = %d, ", t, G->infoVertex[t].pi);
    }
}
/*FINE FUNZIONI DIJKSTRA*/

/*[META PIU' ECONOMICA]Criterio:
Per la scelta della meta piu' economica restituiamo uno dei nodi adiacenti al nodo d'ingresso
poiche' basandoci sui prezzi degli archi, quelli adiacenti al nodo avranno obbligatoriamente
il prezzo minimo possibile, siccome con degli scali i prezzi degli archi sarebbero sommati e quindi di conseguenza
la meta successiva avra' un prezzo sempre superiore.*/
int destinationCheaper(Graph G, int nodeDeparture){//[META PIU' ECONOMICA]Ritorna la citta' meta/nodo piu' economica per la citta' di partenza/nodo inserita
    printf("Inizio calcolo meta piu' economica da %s\n", G->infoVertex[nodeDeparture].name);
    int node = -1;
    int min = INT_MAX;
    if (G != NULL) {
        List e = G->adj[nodeDeparture];
        if (e == NULL) {
            puts("La citta' di partenza non ha possibili destinazioni, verra' restituito -1\n");
        } else {
            while (e != NULL) {
                if (e->price < min) {
                    node = e->target;
                    min = e->price;
                }
                e = e->next;
            }
        }
        printf("La meta piu' economica da %s e' : %s", G->infoVertex[nodeDeparture].name, G->infoVertex[node].name);
    }
    return node;
}

/*[META PIU' GETTONATA]Criterio:
In base ad una citta' data in ingresso(citta' di partenza) restituisce la meta/nodo piu' gettonata
Ovvero "la meta piu' gettonata per una citta' " e' quella la quale puo' essere raggiunta dalla citta' di partenza
Quindi esiste una tratta/collegamento tra la citta' di partenza e la citta' d'arrivo
e che tra tutte quelle cui esiste una tratta ha il punteggio di citta' (punteggio gettonato) massimo

Nel caso in cui la meta 'col punteggio gettonato massimo'  sia piu' di una per una citta' data in partenza
Ovvero due o piu' possibili mete hanno lo stesso punteggio, allora l'utente decide
La citta' di partenza e' esclusa dalle possibili destinazioni
*/

int destinationMostPopular(Graph G, int nodeDepartureCity) {//[META PIU' GETTONATA]Ritorna la citta' meta/nodo piu' gettonata per la citta' di partenza/nodo inserita
    printf("Inizio calcolo della citta' di destinazione piu' gettonata per la citta' %s\n",G->infoVertex[nodeDepartureCity].name);
    int max = 0;
    int result = -1; //Nel caso in cui la citta' di partenza non avesse destinazioni
    //trovo la citta' con punteggio massimo tra quelle che hanno un collegamento col nodo di partenza
    for (int i = 0; i < G->nodes_count; i++) {
        if (existLinkDfs(G, nodeDepartureCity, i) == 1) { //se esiste il collegamento
            if (i != nodeDepartureCity) {//la citta' di partenza e' esclusa tra quelle di destinazione
                if (max < G->infoVertex[i].cityPopularPoints) {
                    max = G->infoVertex[i].cityPopularPoints;
                    result = G->infoVertex[i].key; //nodo col punteggio massimo
                }
            }
        }
    }

    int nodiTrovati[G->nodes_count]; //vettore di nodi/citta' trovati con lo stesso punteggio massimo, al max possono eguagliare tutti i nodi del grafo
    int indexTrovati = 0;
    for (int i = 0; i < G->nodes_count; i++) {
        if (existLinkDfs(G, nodeDepartureCity, i) == 1) {
            if (i != nodeDepartureCity) {
                if (max == G->infoVertex[i].cityPopularPoints) {//se il punteggio e' uguale a quello massimo, mi salvo i nodi trovati
                    nodiTrovati[indexTrovati] = G->infoVertex[i].key;
                    indexTrovati++;
                }
            }
        }
    }

    if (indexTrovati > 1) {
        printf("\nSono state trovate %d citta' ugualmente gettonate con il punteggio di %d per la citta' di partenza %s\n", indexTrovati, max, G->infoVertex[nodeDepartureCity].name);
        printf("\nSeleziona: \n");
        for (int i = 0; i < indexTrovati; i++) {
            int key = nodiTrovati[i];
            printf("%d = %s con %d punti\n", (i + 1), G->infoVertex[key].name, G->infoVertex[key].cityPopularPoints);
        }
        int scelta;
        puts("Inserisci il numero del vertice che vuoi tra quelli visualizzati:");
        scanf("%d", &scelta);
        getchar();
        while ((scelta < 1) || (scelta > indexTrovati)) {
            puts("SCELTA NON CONSENTITA,Inserisci il numero del vertice che vuoi tra quelli visualizzati:");
            scanf("%d", &scelta);
            getchar();
        }
        //scelta va' -1 perche' sono visualizzati i numeri da 1 a indexTrovati che possono essere selezionati
        result = nodiTrovati[scelta - 1];
        printf("Scelto nodo  %d = %s come destinazione piu' gettonata\n", result, G->infoVertex[result].name);

    } else if (indexTrovati == 1) {
        printf("Scelto nodo  %d come destinazione piu' gettonata, esso e' l'unico nodo con punteggio gettonate massimo per la citta'di partenza %d\n",result, nodeDepartureCity);
    } else {
        printf("la citta'di partenza %d non ha destinazioni, e' solo una citta' di arrivo, sara' restituito '-1'\n",nodeDepartureCity);
    }
    return result;
}


void printNodeLinks(Graph G, int node) {//Stampa tutti i nodi con cui e' collegato/ha una tratta il nodo in ingresso
    if (G != NULL) {
        if ((node >= 0) && (node <= G->nodes_count)) {
            printf("\nStampa collegamenti per il nodo:[%d/%s]\nE' collegato/ha tratte con : ", node,G->infoVertex[node].name);
            for (int i = 0; i < G->nodes_count; i++) {
                if (i != node) {//il nodo in ingresso e' escluso
                    if (existLinkDfs(G, node, i) == 1) {
                        printf("[%d/%s] ", i, G->infoVertex[i].name);
                    }
                }
            }
            printf("\n\n");
        } else {
            puts("Il nodo non appartiene al grafo");
        }
    } else {
        puts("Il grafo e' vuoto");
    }

}

int existLinkDfs(Graph G, int v1,int v2) { //Visita il grafo tramite dfs e controlla se e' possibile raggiungere un vertice v2 partendo da v1 pur passando da altri vertici (quindi nelle loro liste d'adiacenza)
    int trovato = 0;
    int scalo = 0;
    int *aux = calloc(G->nodes_count,sizeof(int));
    if (!aux) {
        printf("Errore, vettore ausiliario nella funzione 'dfs' non allocato.\n");
    } else {
        if (listContainsVertex(G, v1, v2) == 1) { //se c'e' arco diretto tra v1 e v2, quindi v2 e' contenuto nella lista d'adiacenza di v1 e' fatto
            trovato = 1;
        } else {//altrimenti vediamo se si puo' raggiungere v2 tramite gli altri vertici collegati a v1
            existLinkDfs1(G, v1, aux, v2, &trovato);
            scalo = 1;
        }
    }
    free(aux);
    return trovato;
}

//Seconda parte del controllo tratta tramite DFS
//questo metodo cicla per ogni elemento della lista d'adiacenza del vertice 'i' passato dal DFS
//ed esegue la ricorsione se 'i' non e' gia' stato visitato E non ha trovato il vertice di destinazione
void existLinkDfs1(Graph G, int i, int *aux, int verticeDiDestinazione, int *val) {
    List e;
    aux[i] = 1;
    e = G->adj[i];
    while ((e != NULL) && (*val == 0)) {
        if (e->target == verticeDiDestinazione) { //se ho trovato il vertice di destinazione nel primo nodo di 'e' mi fermo, altrimenti richiamo ricorsivamente dfs1
            *val = 1;
            e = e->next;
        } else if (!aux[e->target]) {//Se il vertice contenuto nel nodo puntato da 'e' non e' stato gia' visitato, usiamo una chiamata ricorsiva
            existLinkDfs1(G, e->target, aux, verticeDiDestinazione, val);
            e = e->next;
        } else {
            e = e->next;
        }
    }
}

int listContainsVertex(Graph G, int v1,int v2) {//Restituisce 1 se nella lista d'adiacenza del vertice v1 e' presente un nodo che ha come target=v2, 0 altrimenti
    int trovato = 0;
    if (G != NULL) {
        List e = G->adj[v1];
        while ((e != NULL) && (trovato == 0)) {
            if (e->target == v2) {
                trovato = 1;
            } else {
                e = e->next;
            }
        }
    }
    return trovato;
}

/*Funzioni infoVertex*/
void addInfoVertex(Graph G) {//Aggiunge una cella al vettore di informazioni sul vertice
    if (G != NULL) {
        Vertex *old = G->infoVertex;
        int i = 0;
        G->infoVertex = (Vertex *) malloc((G->nodes_count + 1) * sizeof(Vertex));
        for (i = 0; i < G->nodes_count; i++) {
            strcpy(G->infoVertex[i].name, old[i].name);
            G->infoVertex[i].key = old[i].key;
            G->infoVertex[i].cityPopularPoints = old[i].cityPopularPoints;
            G->infoVertex[i].d = old[i].d;
            G->infoVertex[i].pi = old[i].pi;
        }
        G->infoVertex[G->nodes_count].key = G->nodes_count;
        strcpy(G->infoVertex[G->nodes_count].name, "NO_NAME");
        G->infoVertex[G->nodes_count].cityPopularPoints = 0;
        G->infoVertex[G->nodes_count].d = -1;
        G->infoVertex[G->nodes_count].pi = -1;
    }
}

void removeInfoVertex(Graph G, int n) {//Rimuove le informazioni di un vertice
    int i = 0;
    int x = 0;
    printf("Nome corrispondente al nodo %d e' %s\n", n, G->infoVertex[n].name);
    Vertex *old = G->infoVertex;
    G->infoVertex = (Vertex *) malloc((G->nodes_count - 1) * sizeof(Vertex));
    for (i = 0; i < G->nodes_count; i++) {
        if (i != n) {
            strcpy(G->infoVertex[x].name, old[i].name);
            G->infoVertex[x].key = x;
            G->infoVertex[x].cityPopularPoints = old[i].cityPopularPoints;

            if (old[i].pi != n) {//se il predecessore non e' uguale al nodo rimosso
                G->infoVertex[x].d = old[i].d;
                G->infoVertex[x].pi = old[i].pi;
            } else {
                G->infoVertex[x].d = -1;
                G->infoVertex[x].pi = -1;
            }

            x++;
        }
    }
    free(old);
}

void printGraphInfoVertex(Graph G) {//Stampa il vettore con tutte le informazioni dei vertici del grafo
    puts("\n\nStampa VETTORE INFOVERTEX del Grafo.");
    for (int i = 0; i < G->nodes_count; i++) {
        int key = G->infoVertex[i].key;
        char *name = G->infoVertex[i].name;
        int points = G->infoVertex[i].cityPopularPoints;
        int d = G->infoVertex[i].d;
        int pi = G->infoVertex[i].pi;
        printf("[i=%d] key=%d , name=%s , cityPopularPoints=%d , d=%d , pi=%d \n", i, key, name, points, d, pi);
    }
}

void setNodeName(Graph G, int nVertex, char name[]) { //associa il nome al vertice dato in ingresso
    if ((nVertex >= 0) && (nVertex <= G->nodes_count)) {
        strcpy(G->infoVertex[nVertex].name, name);
    } else {
        printf("il vertice %d non appartiene al grafo, impossibile associare il nominativo.\n", nVertex);
    }
}


char *getNodeName(Graph G, int nVertex) {//Ritorna il nome corrispondente al nodo numerico
    return G->infoVertex[nVertex].name;
}


int getNodeFromName(Graph G, char name[]) {//Ritorna il corrispettivo numerico al nodo dato in input come nome
    int trovato = 0;
    int i = 0;
    int result = -1;
    char nameVertex[50];
    char nameToFind[50];

    strtolower(name, nameToFind);

    while ((i < G->nodes_count) && (trovato == 0)) {
        strtolower(G->infoVertex[i].name, nameVertex);

        if ((strcmp(nameVertex, nameToFind)) == 0) {
            trovato = 1;
            result = G->infoVertex[i].key;
        } else {
            i++;
        }
    }
    if (trovato == 0) {
        puts("non esiste un corrispondente numerico del nome inserito");
    }
    return result;
}


void printGraphOnlyWithNames(Graph G) {//Stampa il grafo solo coi nominativi dei vertici
    int ne = 0;//numero totale degli archi
    if (G != NULL) {
        printf("[INIZIO STAMPA GRAFO]\nIl grafo ha %d vertici\n\n", G->nodes_count);
        for (int i = 0; i < G->nodes_count; i++) {
            printf("Vertice: [%s] -> ", G->infoVertex[i].name);
            List e = G->adj[i];
            while (e != NULL) {
                printf("[V:%s  PREZZO:%d   KM:%d]; ", G->infoVertex[e->target].name, e->price, e->km);
                ne = ne + 1;
                e = e->next;
            }
            puts("\n");
        }
        printf("Il grafo ha %d archi\n[FINE STAMPA GRAFO]\n", ne);
    } else {
        puts("Il grafo e' vuoto");
    }
}


void printGraphIndexNameAndPoints(Graph G) {// Stampa il grafo con gli indici relativi ed i nomi delle citta' presenti con il punteggio di gettonamento associato
    puts("\n\nStampa Citta'.");
    for (int i = 0; i < G->nodes_count; i++) {
        char *name = G->infoVertex[i].name; //gli do' solo l'indirizzo
        int point = G->infoVertex[i].cityPopularPoints;//
        printf("[%d] Nome=%s - Punteggio citta' gettonata =%d\n", i,name,point);
    }
}

void setNodeCityPopularPoints(Graph G, int nVertex, int points) {//Assegna i punti 'gettonati' al nodo(vertice/citta') dato in input
    G->infoVertex[nVertex].cityPopularPoints = points;
}

int getNodeCityPopularPoints(Graph G, int nVertex) {//Ritorna i punti 'gettonati' del nodo(vertice/citta') dato in input
    return G->infoVertex[nVertex].cityPopularPoints;
}

void printCityPopularPoints(Graph G) {//Stampa tutti i nodi/citta' coi punteggi gettonati associati
    puts("\nSTAMPA dei Punteggi di ogni citta'/nodo appartenenti al grafo.");
    for (int i = 0; i < G->nodes_count; i++) {
        printf("Vertice/Citta': [%d/%s] -- Punteggio citta' gettonata %d\n", i, G->infoVertex[i].name,
               G->infoVertex[i].cityPopularPoints);
    }
    puts("FINE Stampa.\n");
}

void printGraphWithNames(Graph G) {// stampa il grafo completo coi nomi associati ai vertici numerici
    int ne = 0;
    if (G != NULL) {
        printf("[INIZIO STAMPA GRAFO]\nIl grafo ha %d vertici\n\n", G->nodes_count);
        for (int i = 0; i < G->nodes_count; i++) {
            printf("Vertice: [%d/%s] -> ", i, G->infoVertex[i].name);
            List e = G->adj[i];
            while (e != NULL) {
                printf("[V:%d/%s  PREZZO:%d   KM:%d]; ", e->target, G->infoVertex[e->target].name, e->price, e->km);
                ne = ne + 1;
                e = e->next;
            }
            puts("\n");
        }
        printf("Il grafo ha %d archi\n[FINE STAMPA GRAFO]\n", ne);
    } else {
        puts("Il grafo e' vuoto");
    }
}

City getAllCityFromGraph(Graph G) {//Restituisce una lista di city con tutte le citta' del grafo
    City city = NULL;

    if (G != NULL) {
        for (int i = 0; i < G->nodes_count; i++) {
            city = enqueueCity(city, G->infoVertex[i].name);
        }
    } else
        puts("Il grafo e' vuoto");

    return city;
}

/*Funzioni degli archi*/
void setKm(Graph G, int v1, int v2, int km) {//Assegna il peso 'km' all'arco (v1,v2) appartenente al grafo G
    if (!isEmpty(G)) {
        if (containsEdge(G, v1, v2)) {
            List e = G->adj[v1];
            int trovato = 0;
            while ((e != NULL) && (trovato == 0)) {
                if (e->target == v2) {
                    e->km = km;
                    trovato = 1;
                } else {
                    e = e->next;
                }
            }
        } else {
            puts("L'arco non e' contenuto nel grafo, impossibile assegnare peso.\n");
        }
    }
}

int getKm(Graph G, int v1, int v2) {//Restituisce i km dell'arco (v1,v2) appartenente al grafo G, -1 altrimenti
    int km = 0;
    if (!isEmpty(G)) {
        if (containsEdge(G, v1, v2)) {
            List e = G->adj[v1];
            int trovato = 0;
            while ((e != NULL) && (trovato == 0)) {
                if (e->target == v2) {
                    km = e->km;
                    trovato = 1;
                } else {
                    e = e->next;
                }
            }
        } else {
            puts("L'arco non e' contenuto nel grafo, impossibile ottenere peso,sara' restituito 0.\n");
        }
    }
    return km;
}

void setPrice(Graph G, int v1, int v2, int price) {//Assegna il peso 'price' all'arco (v1,v2) appartenente al grafo G, 0 altrimenti
    if (!isEmpty(G)) {
        if (containsEdge(G, v1, v2)) {
            List e = G->adj[v1];
            int trovato = 0;
            while ((e != NULL) && (trovato == 0)) {
                if (e->target == v2) {
                    e->price = price;
                    trovato = 1;
                } else {
                    e = e->next;
                }
            }
        } else {
            puts("L'arco non e' contenuto nel grafo, impossibile assegnare peso.\n");
        }
    }
}

int getPrice(Graph G, int v1, int v2) {//Restituisce il peso dell'arco (v1,v2) appartenente al grafo G, 0 altrimenti
    int price = 0;
    if (!isEmpty(G)) {
        if (containsEdge(G, v1, v2)) {
            List e = G->adj[v1];
            int trovato = 0;
            while ((e != NULL) && (trovato == 0)) {
                if (e->target == v2) {
                    price = e->price;
                    trovato = 1;
                } else {
                    e = e->next;
                }
            }
        } else {
            puts("L'arco non e' contenuto nel grafo, impossibile ottenere peso,sara' restituito 0.\n");
        }
    }
    return price;
}


List removeEdge(Graph G, int source, int target){// Rimuove un arco specificando sorgente e target,restituisce la lista degli archi modifcata
    printf("\nInizio rimozione Arco (%d,%d).\n", source, target);
    if (G == NULL) {
        puts("Il grafo non e' allocato, impossibile aggiungere un arco.");
    } else if (existVertici(G, source, target) == true) {
        if (containsEdge(G, source, target) == 0) {
            printf("L'arco (%d,%d) non esiste nel grafo, IMPOSSIBILE RIMUOVERLO.\n", source, target);
        } else {
            G->adj[source] = removeNodeList(G->adj[source], target);
            printf("Rimozione dell'arco (%d,%d) completata.\n\n", source, target);
        }
    } else {
        printf("I vertici dell'arco da rimuovere non appartengono al grafo, rimozione annullata\n");
    }
    return G->adj[source];
}


void addEdgeWithoutPrints(Graph G, int source, int target, int price, int km) {//Aggiunge un arco al grafo coi rispettivi controlli senza stampe
    if (G == NULL) {
        puts("Il grafo non e' allocato, impossibile aggiungere un arco.");
        return;
    }
    if (containsEdge(G, source, target) == 1) {
        printf("L'arco (%d,%d) e' gia' presente nel grafo.\n", source, target);
    } else {
        if (source != target) {
            G->adj[source] = appendNodeList(G->adj[source], target, price, km);
        }
    }
}


void addEdge(Graph G, int source, int target, int price, int km) {// Aggiunge al grafo G un arco da sorgente a target con prezzo 'price' e km 'km
    printf("Inizio inserimento arco (%d,%d) con prezzo:%d e km:%d nel grafo PESATO.\n", source, target, price, km);
    if (G == NULL) {
        puts("Il grafo non e' allocato, impossibile aggiungere un arco.");
        return;
    }
    if (containsEdge(G, source, target) == 1) {
        printf("L'arco (%d,%d) e' gia' presente nel grafo.\n", source, target);
    } else {
        if (source != target) {
            G->adj[source] = appendNodeList(G->adj[source], target, price, km);
            puts("Inserimento arco nel GRAFO PESATO completato.\n");
        }
    }
    puts("Inserimento arco nel GRAFO PESATO completato.\n");

}

int containsEdge(Graph G, int vertice1, int vertice2) {//Ritorna 1 se l'arco(vertice1,vertice2) e' presente(contenuto) nel grafo, 0 altrimenti, e controlla che i vertici appartengano al grafo
    int trovato = 0;
    List e;
    if (isEmpty(G)) {
        puts("grafo vuoto");
    } else if ((existVertici(G, vertice1, vertice2)) == false) {
        printf("Uno o entrambi i vertici inseriti non sono del grafo, inserimento annullato\n");
        return trovato;
    } else if (G->adj[vertice1] != NULL) {
        e = G->adj[vertice1];
        while ((e != NULL) && (trovato == 0)) {
            if (e->target == vertice2) {
                trovato = 1;
            } else {
                e = e->next;
            }
        }
    }
    return trovato;
}

bool existVertici(Graph G, int v1, int v2) {
    return v1 >= 0 && v1 <= G->nodes_count - 1 && v2 >= 0 && v2 <= G->nodes_count - 1;
}

/*Funzioni dei nodi/vertici*/
void addNode(Graph G) {// Aggiunge un nodo al grafo, e richiama addInfoVertex che aggiunge una posizione al vettore di informazioni associate al nuovo nodo
    if (G != NULL) {
        List *old = G->adj;
        int i = 0;
        G->adj = (List *) malloc((G->nodes_count + 1) * sizeof(List));
        for (i = 0; i < G->nodes_count; i++)
            G->adj[i] = old[i];

        G->adj[G->nodes_count] = NULL;
        addInfoVertex(G); //aggiunta di un nuovo nodo nel vettore di informazioni
        G->nodes_count += 1;
    }
}

void removeNode(Graph G, int node_to_remove) {// Rimuove un nodo dal grafo, sistemando gli indici e riallocando la memoria,e richiama removeInfoVertex per rimuovere le info del nodo rimosso
    if (G != NULL) {
        printf("Inizio rimozione nodo %d dal grafo.\n", node_to_remove);
        int i = 0;
        int x = 0;
        List *tmp = G->adj;
        G->adj = (List *) calloc(G->nodes_count - 1, sizeof(List));
        for (i = 0; i < G->nodes_count; i++) {
            if (i != node_to_remove) {
                G->adj[x] = checkListRemoval(tmp[i], node_to_remove);
                x++;
            } else {
                freeList(tmp[i]);
            }
        }
        free(tmp);
        removeInfoVertex(G, node_to_remove); //rimozione del nodo anche dal vettore di informazioni
        G->nodes_count = G->nodes_count - 1;
        printf("Rimozione nodo %d completata.\n\n", node_to_remove);
    }
}


List checkListRemoval(List L, int node_to_remove) {//Rimuove il nodo contentente l'intero 'node_to_remove' dalla lista L e restituisce il puntatore alla lista
    if (L != NULL) {
        L->next = checkListRemoval(L->next, node_to_remove);
        if (L->target == node_to_remove) {
            List tmp = L->next;
            free(L);
            return tmp;
        } else if (L->target > node_to_remove) {
            L->target -= 1;
        }
    }
    return L;
}

int getKeyVertexFromGraph(Graph g, City city) {
    int key = -1;

    for (int i = 0; i < g->nodes_count; i++) {
        if (strcmp(g->infoVertex[i].name, city->name) == 0) {
            key = g->infoVertex[i].key;
        }
    }

    return key;
}

//Punto 1 traccia Progetto
ListUserBooking bookingCheaperOrShortestPath(Graph g, int departureKey, int destinationKey, ListUserBooking listUserBooking,User user) {
    City cityTravel = NULL;

    if (choiceBetweenTwo("\nSeleziona:\n1 - Tratta piu' economica\n2 - Tratta piu' breve\n") == 1) {
        dijkstraCheaper(g, departureKey);
    } else {
        dijkstraShortestDistance(g, departureKey);
    }

    cityTravel = getSP(g, departureKey, destinationKey);

    int price = getFlyCost(g, departureKey, destinationKey); //Ottiene il costo della tratta dopo il calcolo effettuato da dijkstra

    char departureName [50];
    char destinationName [50];

    strcpy(departureName , getNodeName(g,departureKey));
    strcpy(destinationName , getNodeName(g,destinationKey));

    int confirmPurchase = summaryPurchase(price,departureName,destinationName, user); //Effettua i calcoli relativi ai costi ed ottiene la decisione dell'utente sulla conferma o meno della prenotazione

    if (confirmPurchase == 1){
        Booking bookingTravel = enqueueBooking(NULL, price, cityTravel);

        UserBooking userBooking = getUserBookingFromListUserBooking(listUserBooking, user);

        UserBooking userBookingTravel = addBookingToUserBooking(userBooking, user, bookingTravel);

        if (listUserBooking == NULL)
            listUserBooking = createListUserBooking(userBookingTravel);
        else
            listUserBooking = enqueueListUserBooking(listUserBooking, userBookingTravel);

        printf ("\nPrenotazione effetuata con successo\nGrazie %s\n",user->name);

    }else{
        printf ("\nPrenotazione ANNULLATA\n");
    }


    return listUserBooking;
}

//Gestisce la parte conclusiva della prenotazione , permettendo all'utente di spendere i propri punti per completare la prenotazoine
//gestisce il metodo di acquisizione dei nuovi punti che guadagnera' dalla nuova prenotzione
//mostra a schermo il costo della prenotazione comprensiva dello sconto eventuale
int summaryPurchase(int priceOfPurchase, char departureName [], char destinationName [], User user){

    int  confirmOperation, confirmUseOfPoints, addNewPoints, initialPoints;
    printf("\nRiepilogo prenotazione: Da %s  A  %s\n", departureName, destinationName);


    printf("Il prezzo di listino della prenotazione e' %d Euro\n",priceOfPurchase);
    if (user->points > 0){

        printf("\nHai attualmente %d punti equivalenti a %d Euro\n",user->points, user->points);
        printf("desideri utilizzarli per l'acquisto del biglietto?\n");
        printf("\n1 - Si\n2 - No\n");
        scanf("%d", &confirmUseOfPoints);

        while (confirmUseOfPoints != 1 && confirmUseOfPoints != 2) {

            printf("\nHai attualmente %d punti equivalenti a %d Euro\n ",user->points, user->points);
            printf("desideri utilizzarli per l'acquisto del biglietto?\n");
            scanf("%d", &confirmUseOfPoints);
        }
             initialPoints =  user->points;
        if (confirmUseOfPoints == 1){
            if (priceOfPurchase < user->points){
                user->points = user->points - priceOfPurchase;
                priceOfPurchase = 0;
            }

            if (priceOfPurchase >= user->points){
                priceOfPurchase = priceOfPurchase - user->points;
                user->points = 0;
            }
        }
    }

    addNewPoints = priceOfPurchase / 2;

    printf("Prezzo totale prenotazione:  %d Euro\n", priceOfPurchase);
    printf("Acquistando questo viaggio guadagnerai: %d punti\n", addNewPoints);
    while (confirmOperation != 1 && confirmOperation != 2) {
        printf("\nCosa desideri fare :\n1 - Conferma ed acquista il biglietto\n2 - Annulla operazione\n\n");
        scanf("%d", &confirmOperation);
        getchar();
    }
    if (confirmOperation == 1){

        user->points = user->points + addNewPoints;

    }
    if (confirmOperation == 2){
        user->points = initialPoints;

    }
    return  confirmOperation;
}


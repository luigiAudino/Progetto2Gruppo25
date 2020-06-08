#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include "../Util/util.h"
#include "graph.h"
#include "../Input/inputReader.h"

#define EDGE_SUCC 0.33 //indica la percentuale di successo di creazione di un arco


/*
void graphEditorMenu(Graph G) { //Effettua modifiche varie nel grafo G, chiamabile anche se il grafo era preesistente
    while(1) {
        printGraph(G);
        printf("1 - Aggiungi nodo\n2 - Rimuovi nodo\n3 - Aggiungi arco\n4 - Rimuovi arco\n5 - Stampa\n6 - Fine\nInput  ->  ");
        int input = 0;
        while(!getPositive(&input) || input>6 || input<0);
        switch(input) {
            case 1: {
                addNode(G);
                break;
            }
            case 2: {
                int nodo = -1;
                printf("Vertice da rimuovere:\t");
                while(!getPositive(&nodo) || nodo>=G->nodes_count) { printf("Selezione del nodo non valida. Riprovare\n"); }
                removeNode(G, nodo);
                break;
            }
            case 3: {
                int sorgente = 0;
                printf("Vertice sorgente:\t");
                while(!getPositive(&sorgente) || sorgente>=G->nodes_count) {printf("Selezione del nodo non valida. Riprovare\n"); }
                int destinazione = 0;
                printf("Vertice destinazione:\t");
                while(!getPositive(&destinazione) || destinazione>=G->nodes_count) {printf("Selezione del nodo non valida. Riprovare\n"); }
                int peso = 0;
                printf("Peso:\t");
                while(!getInt(&peso)) { printf("Peso non valido. Riprovare\n"); }
                addEdge(G, sorgente, destinazione, peso);
                break;
            }
            case 4: {
                int sorgente = 0;
                printf("Vertice sorgente:\t");
                while(!getPositive(&sorgente) || sorgente>=G->nodes_count) {printf("Selezione del nodo non valida. Riprovare\n"); }
                int destinazione = 0;
                printf("Vertice destinazione:\t");
                while(!getPositive(&destinazione) || destinazione>=G->nodes_count) {printf("Selezione del nodo non valida. Riprovare\n"); }
                removeEdge(G, sorgente, destinazione);
                break;
            }
            case 5: {
                printGraph(G);
                break;
            }
            case 6: {
                return;
            }
        }
    }
}

Graph graphCreationMenu(int n) {
    Graph G=NULL;
    int input=1;
    do{
        if(input==0 || input>3) printf("Nessuna azione associata al codice %d\n",input);
        printf("Seleziore il metodo di creazione del nuovo grafo :\n");
        printf("1) Grafo vuoto\n");
        printf("2) Grafo popolato da archi forniti in input\n");
        printf("3) Grafo popolato da archi random\n");
    } while(!getPositive(&input) || input>3 || input==0);

    if(input>1){
        if (n<=0) {
            do{
                printf("Quanti nodi ha il grafo?\n");
            }
            while(!getPositive(&n));
        }
        if(input==2){
            G=initGraph(n);
            graphEditorMenu(G);
        } else {
            G=randomGraph(n);
        }
    } else {
        G=initGraph(0);
    }

    return G;
}
*/

//Inizializzazione del grafo pre-settato con 20 mete e tratte
Graph presetGraph(Graph G){
    G = initGraph(20);
    setGraph(G);

    //0
    addEdgeWithoutPrints(G,0,1,43,775);
    addEdgeWithoutPrints(G,0,2,71,230);
    //1
    addEdgeWithoutPrints(G,1,3,87,1034);
    //2
    addEdgeWithoutPrints(G,2,0,163,230);
    addEdgeWithoutPrints(G,2,3,84,573);
    addEdgeWithoutPrints(G,2,4,44,922);
    addEdgeWithoutPrints(G,2,6,157,595);
    //3
    addEdgeWithoutPrints(G,3,5,46,1095);
    //4
    addEdgeWithoutPrints(G,4,3,84,573);
    //5
    //non ha archi uscenti
    //6
    addEdgeWithoutPrints(G,6,4,112,464);
    addEdgeWithoutPrints(G,6,7,55,934);
    addEdgeWithoutPrints(G,6,8,74,913);
    //7
    addEdgeWithoutPrints(G,7,4,103,1585);
    addEdgeWithoutPrints(G,7,8,108,401);
    //8
    addEdgeWithoutPrints(G,8,9,195,153);
    addEdgeWithoutPrints(G,8,10,102,1345);


    return G;
}

Graph initGraph(int nodes_count) { //crea un grafo vuoto
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
        }
    }
    return G;
}


Graph setGraph(Graph G) { //settaggio a NULL della lista d'adiacenza e del vettore di nomi
    for (int i = 0; i < G->nodes_count; i++) {
        G->adj[i] = NULL;  //Inizializzo i puntatori di puntatori facendoli puntare a NULL
        G->infoVertex[i].cityPopularPoints = 0;
        G->infoVertex[i].key = i;
        //i nomi del vettore dei vertici gia' sono inizializzati essendo statici 'name[50]'
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


int
isEmpty(Graph G) { // Se il puntatore al grafo e' NULL, quindi il grafo e' VUOTO (non e' allocato nulla) restituisce 1, 0 altrimenti
    return (G == NULL);
}
/*______________________________________________________________________*/
/*CRITERIO meta piu' gettonata:
//In base ad una citta' data in ingresso(città di partenza) restituisce la meta/nodo piu' gettonata
//Ovvero "la meta piu' gettonata per una citta' " e' quella la quale puo' essere raggiunta dalla citta' di partenza
//Quindi esiste una tratta/collegamento tra la citta' di partenza e la citta' d'arrivo
//e che tra tutte quelle cui esiste una tratta
//ha il punteggio di citta' (punteggio gettonato) massimo
*/

//Nel caso in cui la meta 'col punteggio gettonato massimo'  sia piu' di una per una citta' data in partenza
//Ovvero due o piu' possibili mete hanno lo stesso punteggio, allora l'utente decide
//La citta' di partenza e' esclusa dalle possibili destinazioni

int mostPopularCityFrom(Graph G,int nodeDepartureCity){
    printf("Inizio calcolo della citta'/nodo di destinazione PIU' GETTONATA per il nodo %d/%s\n",nodeDepartureCity,G->infoVertex[nodeDepartureCity].name);
    int max = 0;
    int result;
    //trovo la citta' con punteggio massimo tra quelle che hanno un collegamento col nodo di partenza
    for(int i=0;i<G->nodes_count;i++){
            if(existLinkDfs(G,nodeDepartureCity,i)==1){ //se esiste il collegamento
                if(i!=nodeDepartureCity){//la citta' di partenza e' esclusa tra quelle di destinazione
                    if( max < G->infoVertex[i].cityPopularPoints){//se ci sta un nuovo massimo lo salvo
                        max = G->infoVertex[i].cityPopularPoints;
                        result = G->infoVertex[i].key; //nodo col punteggio massimo
                    }
                }//if dell esclusione
        }
    }

    //Potrebbe capitare che ci siano piu' citta' con pari 'punteggio gettonate' MASSIMO come possibili destinazioni per la citta' data in ingresso
    //le metto tutte in un vettore nel caso queste siano piu' di una e poi faccio decidere all'utente
    int nodiTrovati[G->nodes_count]; //vettore di nodi/citta' trovati con lo stesso punteggio massimo, al max possono eguagliare tutti i nodi del grafo
    int indexTrovati=0;
    for(int i=0;i<G->nodes_count;i++){
        if(existLinkDfs(G,nodeDepartureCity,i)==1){
            if(max==G->infoVertex[i].cityPopularPoints){//se il punteggio e' uguale a quello massimo, mi salvo i nodi trovati
                    nodiTrovati[indexTrovati]= G->infoVertex[i].key;
                    indexTrovati++;
            }
        }
    }

    if(indexTrovati>1){
        printf("Sono stati trovati %d citta' con lo stesso punteggio di gettonate = %d  per il nodo in ingresso = %d \n",indexTrovati,G->infoVertex[result].cityPopularPoints,nodeDepartureCity);
        for(int i=0;i<indexTrovati;i++){
            int key = nodiTrovati[i];
            printf("scelta[%d] = %d/%s con %d punti\n",i,nodiTrovati[i],G->infoVertex[key].name,G->infoVertex[key].cityPopularPoints);
        }
        int scelta;
        puts("Inserisci il numero del vertice che vuoi tra quelli visualizzati:");
        scanf("%d",&scelta);
        while((scelta<0)||(scelta>indexTrovati)){//controllo sulla scelta in input
            puts("SCELTA NON CONSENTITA,Inserisci il numero del vertice che vuoi tra quelli visualizzati:");
            scanf("%d",&scelta);
        }
        result = nodiTrovati[scelta];
        printf("Scelto nodo  %d come destinazione piu' gettonata\n",result);

    }else{
        printf("Scelto nodo  %d come destinazione piu' gettonata, esso e' l'unico nodo con punteggio gettonate massimo per la citta'di partenza %d\n",result,nodeDepartureCity);
    }
    return result;
}



void printNodeLinks(Graph G, int node){//Stampa tutti i nodi con cui e' collegato/ha una tratta il nodo in ingresso
    if(G!=NULL){
        if((node>=0)&&(node<= G->nodes_count)){
            printf("\nStampa collegamenti per il nodo:[%d/%s]\nE' collegato/ha tratte con : ",node,G->infoVertex[node].name);
            for(int i=0;i<G->nodes_count;i++){
                if(i!=node){//il nodo in ingresso e' escluso
                    if(existLinkDfs(G,node,i)==1){
                        printf("[%d/%s] ",i,G->infoVertex[i].name);
                    }
                }
            }
            printf("\n\n");
        }else{//controlli finali
            puts("Il nodo non appartiene al grafo");
        }
    }else{
        puts("Il grafo e' vuoto");
    }

}


//Per visualizzare gli scali decommentare le righe
int existLinkDfs(Graph G,int v1,int v2){ //visita il grafo tramite dfs e controlla se e' possibile raggiungere un vertice v2 partendo da v1 pur passando da altri vertici (quindi nelle loro liste d'adiacenza)
    int trovato = 0;
    int scalo = 0;
    int* aux = calloc(G->nodes_count,sizeof(int)); //un vettore ausiliario della dimensione dei vertici per controllare quale visitiamo e quale no,con calloc e' tutto iniz. a 0
    if(!aux){
        printf("Errore, vettore ausiliario nella funzione 'dfs' non allocato.\n");
    }
    else{ //INIZIO FUNZIONE
          if(listContainsVertex(G,v1,v2)==1){ //se c'e' arco diretto tra v1 e v2, quindi v2 e' contenuto nella lista d'adiacenza di v1 e' fatto
            /*printf("\n[DIRETTO]Trovato collegamento diretto: Il nodo %d ha un collegamento diretto con %d \n",v1,v2);*/
            trovato = 1;
          }
          else{//altrimenti vediamo se si puo' raggiungere v2 tramite gli altri vertici collegati a v1
                //printf("\nNodo(Vertice) del vettore del grafo visitato in DFS: %d\n",v1);
                //printf("indirizzo di trovato1 %p\n",&trovato);
                existLinkDfs1(G,v1,aux,v2,&trovato);
                scalo = 1;
            }
        }
        /*STAMPE SE CI SONO SCALI O MENO
        if((scalo==1)&&(trovato==1)){
            printf("\n[SCALO]Trovato collegamento con scali: Esiste un collegamento con scali tra %d e %d nel grafo\n",v1,v2);
        }
        else if((scalo==0)&&(trovato==1)){
            printf("\n[DIRETTO]Trovato collegamento diretto: Il nodo %d ha un collegamento diretto con %d\n",v1,v2);
        }
        else{
            printf("\nNON ESISTE un collegamento tra %d e %d nel grafo",v1,v2);
        }*/
        //printf("\n\nTROVATO = %d\n\n",trovato);
        free(aux);
        return trovato;
}

//Seconda parte del controllo tratta tramite DFS
//questo metodo cicla per ogni elemento della lista d'adiacenza del vertice i passato dal DFS
//ed esegue la ricorsione se 'i' non e' gia' stato visitato E non ha trovato il vertice di destinazione
void existLinkDfs1(Graph G, int i, int* aux,int verticeDiDestinazione,int* val){
    //printf("indirizzo di trovato1 NEL DFS1  %p\n",val); //il val contiene l'indirizzo di trovato nel DFS, *val e' il contenuto dell'indirizzo puntato da val
    List e; //Puntatore alla lista d'adiacenza che contiene i vertici che fanno un arco col vertice situato nella posizione 'i' del vettore
    aux[i] = 1; //vertice 'i' passato alla funzione e' visitato
    e = G->adj[i];
    while((e!=NULL)&&(*val==0)){ // e deve avanzare col next in ogni if, quindi per  e = al puntatore di posizione i del vettore di puntatori del grafo, finche' "e"  e' vero quindi != NULL, assegna ad ogni ciclo il next ad "e"
            if(e->target==verticeDiDestinazione){ //se ho trovato il vertice di destinazione nel primo nodo di 'e' mi fermo, altrimenti richiamo ricorsivamente dfs1
                //printf("\nvertice di destinazione trovato nella lista di %d tentando di visitare il vertice %d\n",i,e->target);
                *val = 1;
               /*printf("trovato nel ciclo while = %d\n\n",*val);*/
                e = e->next;
               // printf("Nodo %d raggiungibile tramite scali dal vertice di partenza %d\n",verticeDiDestinazione,partenza);
            }
            else if(!aux[e->target]){//Se il vertice contenuto nel nodo puntato da 'e' non e' stato gia' visitato, quindi il suo valore che si trova in aux e' uguale a 0 FAI LA RICORSIONE
                //mi fermo e passo a visitare la lista del vertice contenuto nel nodo, ovvero e->target

                /*printf("Vertice visitato in dfs1: %d che e' contenuto nella lista di %d\n",e->target,i);*/
                existLinkDfs1(G,e->target,aux,verticeDiDestinazione,val);// qui richiamiamo dfs1 per andare a visitare la lista del vertice del (primo) elemento della lista di 'e' che e' uguale ad adj[i] passato da dfs,
                //così scendiamo in profondita' e quando una lista sara' NULL risaliremo ricorsivamente visitando tutti i vertici (nel ciclo while)
                //col quale si creerebbe un ciclo dato che esiste un arco col verticeDiPartenza in questa lista d'adiacenza che stiamo visitando
                e = e->next;
            }
            else{
                e = e->next;
            }
    }
}

int listContainsVertex(Graph G,int v1,int v2){//Restituisce 1 se nella lista d'adiacenza del vertice v1 e' presente un nodo che ha come target=v2, 0 altrimenti
    int trovato = 0;
    if(G!=NULL){
       List e = G->adj[v1];
       while((e!=NULL)&&(trovato==0)){//controllo prima se nella lista di v1 si trova v2
            if (e->target==v2){
                trovato=1;
            }
            else{
                e = e->next;
            }
        }
    }
    return trovato;
}












/*Funzioni del vettore che contiene le informazioni associate ad ogni vertice del grafo---------------------------------------------------------*/



//aggiunge una posizione vuota nel vettore delle infoVertex, da usare quando si aggiunge un vertice/nodo al grafo
void addInfoVertex(Graph G) {
    if (G != NULL) {
        Vertex *old = G->infoVertex;
        int i = 0;
        //G->adj = (List *)realloc(G->adj, (G->nodes_count+1) * sizeof(List));
        G->infoVertex = (Vertex *) malloc((G->nodes_count + 1) * sizeof(Vertex));
        for (i = 0; i < G->nodes_count; i++) { //per ogni campo nuovo del vettore aggiungiamo i vecchi valori
            strcpy(G->infoVertex[i].name, old[i].name);
            G->infoVertex[i].key = old[i].key;
            G->infoVertex[i].cityPopularPoints = old[i].cityPopularPoints;
        }
        G->nodes_count += 1;
    }
}

//rimuove le informazioni del nodo cioe' una posizione la posizione 'n' del vettore infoVertex del grafo.
//e' richiamata in removeNodo
void removeInfoVertex(Graph G, int n) {
    int i = 0;
    int x = 0;
    printf("Nome corrispondente al nodo %d e' %s\n", n, G->infoVertex[n].name);
    Vertex *old = G->infoVertex;
    G->infoVertex = (Vertex *) malloc((G->nodes_count - 1) * sizeof(Vertex));
    for (i = 0; i < G->nodes_count; i++) {
        if (i != n) {
            //printf("\nx=%d i=%d\nIl valore vecchio di %d e' %s\n",x,i,i,old[i].name);
            strcpy(G->infoVertex[x].name, old[i].name);
            //printf("infoVertex[%d] NUOVO = %s\n\n",x,G->infoVertex[x].name);
            G->infoVertex[x].key = old[i].key;
            G->infoVertex[x].cityPopularPoints = old[i].cityPopularPoints;
            x++;
        }
        /*else{
            //free(old);
        }*/
    }
    free(old);
}

//Ritorna un puntatore a struttura Vertex poiche' stiamo modificando il puntatore di infoVertex
Vertex* removeInfoVertexWithArray(Vertex infoVertex[], int node_to_remove, int nodes_count){
    int i = 0;
    int x = 0;
    printf("Nome corrispondente al nodo %d e' %s\n", node_to_remove, infoVertex[node_to_remove].name);
    Vertex *old = infoVertex;
    infoVertex = (Vertex *) malloc((nodes_count - 1)*sizeof(Vertex));
    for (i = 0; i < nodes_count; i++) {
        if (i != node_to_remove) {
            printf("\nx=%d i=%d\nIl valore vecchio di %d e' %s\n",x,i,i,old[i].name);
            strcpy(infoVertex[x].name,old[i].name);
            printf("infoVertex[%d] NUOVO = %s\n\n",x,infoVertex[x].name);
            infoVertex[x].key = old[i].key;
            infoVertex[x].cityPopularPoints = old[i].cityPopularPoints;
            x++;
        }
    }
    free(old);
    return infoVertex;
}

//NON DIMENTICARE di usare lo strcpy altrimenti assegniamo l'indirizzo della variabile, NON AVVIENE LA COPIA del contenuto
void setNodeName(Graph G, int nVertex, char name[]) { //associa il nome al vertice dato in ingresso
    if ((nVertex >= 0) && (nVertex <= G->nodes_count)) {
        strcpy(G->infoVertex[nVertex].name, name);
    } else {
        printf("il vertice %d non appartiene al grafo, impossibile associare il nominativo.\n", nVertex);
    }
}

//Ritorna il nome corrispondente al nodo numerico
char* getNodeName(Graph G, int nVertex) {
    return G->infoVertex[nVertex].name;
}

//Ritorna il corrispettivo numerico al nodo dato in input come nome
int getNodeFromName(Graph G, char name[]) {
    int trovato = 0;
    int i = 0;
    int result = -1;
    char nameVertex[50];
    char nameToFind[50];
    //printf("%s\n",name);
    //funzione che converte la stringa name tutta in caratteri minuscoli nella stringa nameTofind
    strtolower(name, nameToFind);
    //printf("%s\n",nameToFind);

    while ((i < G->nodes_count) && (trovato == 0)) {
        strtolower(G->infoVertex[i].name, nameVertex);
        //printf("%s\n",nameVertex);
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

//Setta i punti 'gettonati' al nodo dato in ingresso
void setNodeCityPopularPoints(Graph G, int nVertex, int points) {
    G->infoVertex[nVertex].cityPopularPoints = points;
}

//Ritorna i punti 'gettonati' per quel nodo
int getNodeCityPopularPoints(Graph G, int nVertex) {
    return G->infoVertex[nVertex].cityPopularPoints;
}

void printCityPopularPoints(Graph G){//Stampa tutti i nodi/citta' coi punteggi gettonati associati
    puts("\nSTAMPA dei Punteggi di ogni citta'/nodo appartenenti al grafo.");
    for (int i = 0; i < G->nodes_count; i++) {
            printf("Vertice/Citta': [%d/%s] -- Punteggio citta' gettonata %d\n", i, G->infoVertex[i].name,G->infoVertex[i].cityPopularPoints);
        }
        puts("FINE Stampa.\n");
}


//stampa del grafo coi nomi
void printGraphWithNames(Graph G) {
    int ne = 0;//numero totale degli archi
    if (G != NULL) {
        printf("[INIZIO STAMPA GRAFO]\nIl grafo ha %d vertici\n\n", G->nodes_count);
        for (int i = 0; i < G->nodes_count; i++) {
            printf("Vertice: [%d/%s] -> ", i, G->infoVertex[i].name);
            List e = G->adj[i];
            while (e != NULL) {//adesso qui scorriamo la lista puntata da 'e', cioe' una lista di Archi
                printf("[V:%d/%s  PREZZO:%d   KM:%d]; ", e->target, G->infoVertex[e->target].name, e->price, e->km);
                ne = ne + 1; //Numero di elementi, cioe' numero totale di archi
                e = e->next; //procediamo al prossimo puntatore nella lista
            }
            puts("\n");
        }
        printf("Il grafo ha %d archi\n[FINE STAMPA GRAFO]\n", ne);
    } else {
        puts("Il grafo e' vuoto");
    }
}


/*funzioni degli archi------------------------------*/

void setKm(Graph G, int v1, int v2, int km) {//Assegna il peso 'km' all'arco (v1,v2) appartenente al grafo G
    if (!isEmpty(G)) {
        if (containsEdge(G, v1, v2)) {
            List e = G->adj[v1];
            int trovato = 0;
            while ((e != NULL) && (trovato == 0)) {
                if (e->target ==
                    v2) { //vuol dire che ho trovato il vertice nella lista d'adiacenza di v1 e quindi l'arco (v1,v2);
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
                if (e->target ==
                    v2) { //vuol dire che ho trovato il vertice nella lista d'adiacenza di v1 e quindi l'arco (v1,v2);
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

void setPrice(Graph G, int v1, int v2,
              int price) {//Assegna il peso 'price' all'arco (v1,v2) appartenente al grafo G, 0 altrimenti
    if (!isEmpty(G)) {
        if (containsEdge(G, v1, v2)) {
            List e = G->adj[v1];
            int trovato = 0;
            while ((e != NULL) && (trovato == 0)) {
                if (e->target ==
                    v2) { //vuol dire che ho trovato il vertice nella lista d'adiacenza di v1 e quindi l'arco (v1,v2);
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
                if (e->target ==
                    v2) { //vuol dire che ho trovato il vertice nella lista d'adiacenza di v1 e quindi l'arco (v1,v2);
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


//magari farlo a void
List removeEdge(Graph G, int source, int target) {
    printf("\nInizio rimozione Arco (%d,%d).\n", source, target);
    if (G == NULL) { //Se G!=NULL il grafo e' allocato e punta a qualcosa, pure se vuoto, si va avanti
        puts("Il grafo non e' allocato, impossibile aggiungere un arco.");//Se G==NULL esisterebbe solo il puntatore a grafo che punta a NULL,
        //return;                                                                //quindi dovremmo creare(quindi allocare in mem) un nuovo grafo da far puntare a G
    } else if (existVertici(G, source, target) == true) { //I vertici che passiamo alla funzione devono esistere nel grafo
        if (containsEdge(G, source, target) == 0) { //se NON contiene l'arco allora return
            printf("L'arco (%d,%d) non esiste nel grafo, IMPOSSIBILE RIMUOVERLO.\n", source, target);
        } else {//superati i controlli rimuove l'arco
            //if (source != target) { ALTRIMENTI BLOCCA GLI ARCHI CICLICI
            G->adj[source] = removeNodeList(G->adj[source], target);
            printf("Rimozione dell'arco (%d,%d) completata.\n\n", source, target);
            // }
        }//fine else dei controlli superati e rimozione dell'arco

    } else {
        printf("I vertici dell'arco da rimuovere non appartengono al grafo, rimozione annullata\n");
    }
    return G->adj[source];
}


//Aggiunge un arco al grafo coi rispettivi controlli senza stampe
void addEdgeWithoutPrints(Graph G, int source, int target, int price, int km){
    if (G == NULL) { //Se G!=NULL il grafo e' allocato e punta a qualcosa, pur se vuoto, si va avanti
        puts("Il grafo non e' allocato, impossibile aggiungere un arco.");
        return;     //Se G==NULL esisterebbe solo il puntatore a grafo che punta a NULL, quindi dovremmo creare(quindi allocare in mem) un nuovo grafo da far puntare a G
    }
    //Controllo esistenza vertici presente in containsEdge()
    if (containsEdge(G, source, target) == 1) { //se contiene gia' l'arco
        printf("L'arco (%d,%d) e' gia' presente nel grafo.\n", source, target);
    } else {
        if (source != target) { //evita archi ciclici
            G->adj[source] = appendNodeList(G->adj[source], target, price, km);
        }
    }
}

//Aggiunge un arco al grafo coi rispettivi controlli
void addEdge(Graph G, int source, int target, int price, int km) {
    printf("Inizio inserimento arco (%d,%d) con prezzo:%d e km:%d nel grafo PESATO.\n", source, target, price, km);
    if (G == NULL) { //Se G!=NULL il grafo e' allocato e punta a qualcosa, pur se vuoto, si va avanti
        puts("Il grafo non e' allocato, impossibile aggiungere un arco.");
        return;     //Se G==NULL esisterebbe solo il puntatore a grafo che punta a NULL, quindi dovremmo creare(quindi allocare in mem) un nuovo grafo da far puntare a G
    }
    //Controllo esistenza vertici presente in containsEdge()
    if (containsEdge(G, source, target) == 1) { //se contiene gia' l'arco
        printf("L'arco (%d,%d) e' gia' presente nel grafo.\n", source, target);
    } else {
        if (source != target) { //evita archi ciclici
            G->adj[source] = appendNodeList(G->adj[source], target, price, km);
            puts("Inserimento arco nel GRAFO PESATO completato.\n");
        }
    }

    puts("Inserimento arco nel GRAFO PESATO completato.\n");

}

//Ritorna 1 se l'arco(vertice1,vertice2) e' presente(contenuto) nel grafo, 0 altrimenti, E CONTROLLA CHE I VERTICI SIANO COMPRESI NEL GRAFO (cioe' >0 e <n-1)
int containsEdge(Graph G, int vertice1, int vertice2) {
    int trovato = 0;
    List e; //puntatore ad un arco/nodo
    if (isEmpty(G)) { // se e' vuoto vale 1 e ritorna 0 perche' sicuramente l'arco non e' presente
        puts("grafo vuoto");
    } else if ((existVertici(G, vertice1, vertice2)) == false) {
        printf("Uno o entrambi i vertici inseriti non sono del grafo, inserimento annullato\n");
        return trovato;
    } else if (G->adj[vertice1] !=
               NULL) { //Se il puntatore contenuto nella pos. 'vertice1' punta a NULL, vuol dire che la sua lista e' vuota e non esiste l'arco tra v1 e v2
        //Se DIVERSO da NULL, il puntatore punta ad almeno un nodo e quindi possiamo andare a controllare se c'e' il vertice v2
        e = G->adj[vertice1];//copiamo il puntatore che e' puntato alla posizione i

        while ((e != NULL) && (trovato ==0)) {//adesso qui scorriamo la lista puntata da 'e'
            if (e->target == vertice2) {
                trovato = 1;
            } else {
                e = e->next; //procediamo al prossimo puntatore nella lista
            }
        }
    }
    return trovato;
}

//Ritorna 1 se 'v1' e 'v2' sono vertici del grafo G, 0 altrimenti
/*int existVertici(Graph G, int v1, int v2) {
    int trovato = 0;
    int limite = G->nodes_count - 1;
    if ((v1 >= 0) && (v1 <= limite)) {
        if ((v2 >= 0) && (v2 <= limite)) {
            trovato = 1;
        }
    }
    return trovato;
}*/

bool existVertici(Graph G, int v1, int v2) {
    return v1 >= 0 && v1 <= G->nodes_count - 1 && v2 >= 0 && v2 <= G->nodes_count - 1;
}

/*fine funzioni archi*/


/*Funzioni dei nodi/vertici---------------------------*/
void addNode(Graph G) {
    if (G != NULL) {
        List *old = G->adj;
        int i = 0;
        //G->adj = (List *)realloc(G->adj, (G->nodes_count+1) * sizeof(List));
        G->adj = (List *) malloc((G->nodes_count + 1) * sizeof(List));
        for (i = 0; i < G->nodes_count; i++)
            G->adj[i] = old[i];
        G->nodes_count += 1;
        G->adj[G->nodes_count - 1] = NULL;
        addInfoVertex(G); //aggiunta di un nuovo nodo nel vettore di informazioni
    }
}

//rimuove il nodo corrispondente alla posizione del nodo da rimuovere, es: nodo da rimuovere = 3, rimuove il nodo di posizione 3
void removeNode(Graph G, int node_to_remove) {
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
                //freeList(G->adj[x]);
                freeList(tmp[i]);
            }
        }
        free(tmp);
        removeInfoVertex(G, node_to_remove); //rimozione del nodo anche dal vettore di informazioni
        G->nodes_count = G->nodes_count - 1;
        printf("Rimozione nodo %d completata.\n\n", node_to_remove);
    }
}


List checkListRemoval(List L, int node_to_remove) {
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
/*fine funzioni dei nodi/vertici*/


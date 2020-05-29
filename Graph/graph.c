#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
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



Graph initGraph(int nodes_count) {
    Graph G = (Graph)malloc(sizeof(struct TGraph));
    if (G==NULL) {
        puts("Impossibile allocare memoria per il grafo.\n");
    }else{
        G->adj = (List *)calloc(nodes_count, sizeof(List));
        if(G->adj==NULL){
            puts("ERRORE: impossibile allocare memoria per il vettore di liste d'adiacenze");
            free(G);
            G=NULL;
            }
            else{
                G->vectorNames = (char**)malloc(sizeof(char*));
                G->nodes_count = nodes_count;
            }
    }
    return G;
}



Graph setGraph(Graph G){
    for(int i=0;i<G->nodes_count;i++){
        G->adj[i]=NULL;  //Inizializzo i puntatori di puntatori facendoli puntare a NULL
        G->vectorNames[i]=(char*)malloc(50*sizeof(char));
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

/*______________________________________________________________________*/

//non mi fa deallocare 'old', free con gli array non funziona
void removeNameFromVector(Graph G,int n){
    int i = 0;
    int x = 0;
    char** old = G->vectorNames;
    G->vectorNames = (char** )calloc(G->nodes_count-1, sizeof(char*));
    for(i=0;i<G->nodes_count;i++){
        if (i != n) {
            G->vectorNames[x] = old[i];
            x++;
        }
        /*else{
        free(old[i]);
        }*/
    }
    //free(old);
}

void setNameVertexInVector(Graph G,int nVertex, char name[]){ //associa il nome al vertice dato in ingresso
    if((nVertex>=0)&&(nVertex<=G->nodes_count)){
    G->vectorNames[nVertex] = name;
    }
    else{
        printf("il vertice %d non appartiene al grafo, impossibile associare il nominativo.\n",nVertex);
    }

}

void printGraphWithNames(Graph G){
    int ne = 0;//numero totale degli archi
    if(G!=NULL){
        printf("Il grafo ha %d vertici\n",G->nodes_count);
        for(int i = 0;i<G->nodes_count;i++){
            printf("Vertice: [%s] -> ",G->vectorNames[i]);
            List e = G->adj[i];
            while(e!=NULL){//adesso qui scorriamo la lista puntata da 'e', cioè una lista di Edge, 'e' è un EdgePtr
                        printf("[V:%s PREZZO:%d KM:%d]; ",G->vectorNames[e->target],e->price,e->km);
                        ne=ne+1; //Numero di elementi, cioè numero totale di archi
                        e= e->next; //procediamo al prossimo puntatore nella lista
                    }
                    puts("\n");
            }
            printf("++++Il grafo PESATO ha %d archi++++\n\n",ne);
        }
        else {
            puts("Il grafo è vuoto");
        }
}




/*funzioni degli archi*/
//farlo a void
List removeEdge(Graph G, int source, int target) {
    printf("\nInizio rimozione Arco (%d,%d).\n",source,target);
    if (G==NULL){ //Se G!=NULL il grafo è allocato e punta a qualcosa, pure se vuoto, si va avanti
            puts("Il grafo non è allocato, impossibile aggiungere un arco.");//Se G==NULL esisterebbe solo il puntatore a grafo che punta a NULL,
            //return;                                                                //quindi dovremmo creare(quindi allocare in mem) un nuovo grafo da far puntare a G
    }else if(existVertici(G,source,target)==1){ //I vertici che passiamo alla funzione devono esistere nel grafo
            if(containsEdge(G,source,target)==0){ //se NON contiene l'arco allora return
                printf("L'arco (%d,%d) non esiste nel grafo, IMPOSSIBILE RIMUOVERLO.\n",source,target);
            }
            else{//superati i controlli rimuove l'arco
                //if (source != target) { ALTRIMENTI BLOCCA GLI ARCHI CICLICI
                    G->adj[source] = removeNodeList(G->adj[source], target);
                    printf("Rimozione dell'arco (%d,%d) completata.\n\n",source,target);
               // }
            }//fine else dei controlli superati e rimozione dell'arco

    }else{
        printf("I vertici dell'arco da rimuovere non appartengono al grafo, rimozione annullata\n");
        }
    return G->adj[source];
}

void addEdge(Graph G, int source, int target, int price, int km) { //
    printf("Inizio inserimento arco (%d,%d) con prezzo:%d e km:%d nel grafo PESATO.\n",source,target,price,km);
    if (G==NULL){ //Se G!=NULL il grafo è allocato e punta a qualcosa, pur se vuoto, si va avanti
            puts("Il grafo non è allocato, impossibile aggiungere un arco.");
            return;     //Se G==NULL esisterebbe solo il puntatore a grafo che punta a NULL, quindi dovremmo creare(quindi allocare in mem) un nuovo grafo da far puntare a G
    }
    if((existVertici(G,source,target)==1)){
        if(containsEdge(G,source,target)==1){ //se contiene già l'arco
            printf("L'arco (%d,%d) e' già presente nel grafo.\n",source,target);
            }
            else{
                if (source != target) {
                G->adj[source] = appendNodeList(G->adj[source], target, price,km);
                }
            }
            puts("Inserimento arco nel GRAFO PESATO completato.\n");
    }
    else{
        printf("Uno o entrambi i vertici inseriti non sono del grafo, inserimento annullato\n");
    }
}


//Ritorna 1 se l'arco(vertice1,vertice2) è presente(contenuto) nel grafo, 0 altrimenti, E CONTROLLA CHE I VERTICI SIANO COMPRESI NEL GRAFO (cioè >0 e <n-1)
int containsEdge(Graph G, int vertice1, int vertice2){
        int trovato = 0;
        List e; //puntatore ad un arco/nodo
        if (isEmpty(G)){ // se è vuoto vale 1 e ritorna 0 perchè sicuramente l'arco non è presente
                puts("grafo vuoto");
        }
        else if((existVertici(G,vertice1,vertice2))==0) {
                puts("CONTROLLO DEI VERTICI DEL CONTAINSEDGE NON SUPERATO,non esiste un arco di vertici non del grafo\n");
                return trovato;
        }
        else if(G->adj[vertice1]!=NULL){ //Se il puntatore contenuto nella pos. 'vertice1' punta a NULL, vuol dire che la sua lista è vuota e non esiste l'arco tra v1 e v2
                                       //Se DIVERSO da NULL, il puntatore punta ad almeno un nodo e quindi possiamo andare a controllare se c'è il vertice v2
               e = G->adj[vertice1];//copiamo il puntatore che è puntato alla posizione i

                    while((e!=NULL)&&(trovato==0)){//adesso qui scorriamo la lista puntata da 'e', cioè una lista di Edge, 'e' è un EdgePtr = LIST
                        if(e->target==vertice2){
                            trovato = 1;
                        }
                        else{
                        e= e->next; //procediamo al prossimo puntatore nella lista
                        }
                    }
            }
    return trovato;
}

//Ritorna 1 se 'v1' e 'v2' sono vertici del grafo G, 0 altrimenti
int existVertici(Graph G, int v1,int v2){
    int trovato = 0;
    int limite = G->nodes_count-1;
    if ((v1>=0)&&(v1<=limite)){
            if((v2>=0)&&(v2<=limite)){
        trovato = 1;
        }
    }
    return trovato;
}
/*fine funzioni archi*/


int isEmpty(Graph G){ // Se il puntatore al grafo è NULL, quindi il grafo è VUOTO (non è allocato nulla) restituisce 1, 0 altrimenti
    return (G==NULL);
}















void addNode(Graph G) {
    if (G != NULL) {
        List * old=G->adj;
        int i=0;
        //G->adj = (List *)realloc(G->adj, (G->nodes_count+1) * sizeof(List));
        G->adj = (List *)malloc((G->nodes_count+1) * sizeof(List));
        for(i=0;i<G->nodes_count;i++)
            G->adj[i]=old[i];
        G->nodes_count += 1;
        G->adj[G->nodes_count-1] = NULL;
    }
}


void removeNode(Graph G, int node_to_remove) {
    if (G != NULL) {
        printf("Inizio rimozione nodo %d dal grafo.\n",node_to_remove);
        int i = 0;
        int x = 0;
        List *tmp = G->adj;
        G->adj = (List *)calloc(G->nodes_count-1, sizeof(List));
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
        removeNameFromVector(G,node_to_remove);/**/
        G->nodes_count -= 1;
        printf("Rimozione nodo %d completata.\n",node_to_remove);
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



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Graph/graph.h"
#include "List/list.h"
#include "User/user.h"
#include "CheckMail/checkMail.h"

void menu();
void backToMenu();

UserTree userTree = NULL;
int roleChoised;
int *ptrRole = &roleChoised;

int main() {

    char cities[7][50] = {"napoli","milano","berlino","roma","palermo","londra","Catania"};

    g = setGraph(g); //assegnamo i valori ai vertici ecc..

    addEdge(g,0,1,1,100);
    addEdge(g,0,3,2,100);

    addEdge(g,1,2,3,100);

    addEdge(g,2,5,4,100);

    addEdge(g,3,0,5,100);
    addEdge(g,3,2,6,100);
    addEdge(g,3,4,7,100);

    addEdge(g,4,2,8,100);

    printGraph(g); //stampa del grafo numerico

    //Assegnazione dei nomi ai vertici del grafo
    for(int i=0;i<g->nodes_count;i++) {
        //printf("valore di i=%d\n",i);
        setNodeName(g, i, cities[i]);
        //printf("Nome aggiunto al vertice %d = %s\n\n",i,g->infoVertex[i].name);
    }

    printGraphWithNames(g);
    /*fine main grafi*/


    setNodeCityPopularPoints(g,2,100);
    setNodeCityPopularPoints(g,3,100000);
    setNodeCityPopularPoints(g,5,100);

    printCityPopularPoints(g);
    printNodeLinks(g,3);

    //int gett = mostPopularCityFrom(g,3);

    //printf("\nScelto nodo piu' gettonato %d=%s",gett,g->infoVertex[gett].name);

    //printGraphWithNames(g);



    /*RILASSAMENTO -------------------------------------------------------------*/
    /*prove dijkstra*/

    int m=1000;
    for(int i=0;i<g->nodes_count;i++) {
        g->infoVertex[i].d = m;
        g->infoVertex[i].pi = 0;
        m++;
    }


    puts("  DISTANZA   - PREDECESSORI  ");
    for(int i=0;i<g->nodes_count;i++) {
        printf("- d[%d] = %d ; ",i,g->infoVertex[i].d); //distanza del vertice 'i' dall origine
        printf("pi[%d] = %d\n",i,g->infoVertex[i].pi);
    }

    printGraph(g);



    //RILASSAMENTO DI OGNI VERTICE
    puts("RILASSAMENTO");
    for(int i=0;i<6;i++){
        List e = g->adj[i];
        printf("\nGiro sulla lista del vertice [%d]\n",i);
        while(e!=NULL){
          relaxKm(g,i,e->target);
          e = e->next;
        }
    }

    puts("STAMPA POST RILASSAMENTO");
    puts("  DISTANZA   - PREDECESSORI  ");
    for(int i=0;i<g->nodes_count;i++) {
        printf("- d[%d] = %d ; ",i,g->infoVertex[i].d); //distanza del vertice 'i' dall origine
        printf("pi[%d] = %d\n",i,g->infoVertex[i].pi);
    }




    Queue q = initQueue();
    for(int i=3;i<g->nodes_count;i++){ //parte da (source+1) poiche' il percorso non puo' andare indietro se non ripassandoci
            enqueue(q,i); //inserisce nella coda il vertice del grafo di cui poi il d[] (infinito nell'algoritmo) della distanza iniziale di ogni vertice
            g->infoVertex[i].d = i;
            //distanzaEprecedenti[i][1] = 0; //come se fosse NULL;
        }

    printf("Min coda %d\n\n\n\n",extractMinDijkstra(g,q));


    Graph k = NULL;
    k = presetGraph(k);
    printGraphWithNames(k);
    printCityPopularPoints(k);
    int gett = mostPopularCityFrom(k,10);

    printf("\nScelto nodo piu' gettonato %d=%s",gett,k->infoVertex[gett].name);

    //printGraphWithNames(g);

    dijkstraCheaper(k,0);
    printSP(k,0,10);

    int dest = destinationCheaper(k,10);

    printf("\nmeta piu' economica = %d\n",dest);


    /*userTree = uploadUsers(userTree);
    userTree = uploadAdmins(userTree);
    menu();*/
    return 0;
}



/*menu' piero e gigi*/
void menu() {
    int choice;
    User user = NULL;
    roleChoised = -1;
    //UserTree userTree = NULL;

    printf("\nSeleziona:\n1 - Login\n2 - Registrazione\n7 - Exit\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            break;
        }

        case 2: {
            break;
        }
        case 7: {
            printf("\nArrivederci!");
            return;
        }

        default: {
            printf("Scelta errata - riprova!\n");
            break;
        }
    }

    if (roleChoised == 1 || roleChoised == 2) {
        if (roleChoised == 1) {
            //USER
            printf("\nNon ci sono operazioni possibili attualmente, ma ti trovi nel menu' dedicato all'utente\n");
        } else {
            //ADMIN
            printf("\nSeleziona:\n3 - Visualizza Utenti\n4 - Visualizza Admin\n5 - Upload users\n6 - Upload admins\n7 - Exit\n");
            scanf("%d", &choice);

            switch (choice) {

                case 3: {
                    if (countUser(userTree) == 0)
                        printf("Non e' presente alcun user!\n");
                    else
                        getAllUserPrint(userTree);

                    break;
                }

                case 4: {
                    if (countAdmin(userTree) == 0)
                        printf("Non e' presente alcun admin!\n");
                    else
                        getAllAdminPrint(userTree);

                    break;
                }

                case 5: {
                    userTree = uploadUsers(userTree);
                    printf("Aggiornata lista users\n");
                    break;
                }
                case 7: {
                    printf("\nArrivederci!");
                    return;
                }

                default: {
                    printf("Scelta errata - riprova!\n");
                    break;
                }
            }
        }
    }




/*
    switch (choice) {
        case 1: {
            login(userTree);
            break;
        }

        case 2: {
            userTree = insertUserNodeTree(userTree, signIn(userTree));
            break;
        }

        case 3: {
            if(countUser(userTree) == 0)
                printf("Non e' presente alcun user!\n");
            else
                getAllUserPrint(userTree);

            break;
        }

        case 4: {
            if(countAdmin(userTree) == 0)
                printf("Non e' presente alcun admin!\n");
            else
                getAllAdminPrint(userTree);

            break;
        }

        case 5: {
            userTree = uploadUsers(userTree);
            printf("Aggiornata lista users\n");
            break;
        }

        case 6: {
            userTree = uploadAdmins(userTree);
            printf("Aggiornata lista admins\n");
            break;
        }

        case 7: {
            printf("\nArrivederci!");
            return;
        }

        default: {
            printf("Scelta errata - riprova!\n");
            break;
        }

    }
*/
    backToMenu();
}

void backToMenu() {
    int choice;

    do {
        printf("\nSeleziona 0 per tornare al menu o 1 per uscire\n");
        scanf("%d", &choice);
    } while (choice != 0 && choice != 1);

    if (choice == 0)
        menu();

    //printf("\nArrivederci!");
}



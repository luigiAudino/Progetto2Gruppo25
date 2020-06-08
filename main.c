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
Graph g = NULL ; //allochiamo la memoria per le variabili del grafo

int main() {

   /*inizio main grafi*/
    char cities[7][50] = {"napoli","milano","berlino","roma","palermo","londra","Catania"};

    g = initGraph(6); //allochiamo la memoria per le variabili del grafo
    g = setGraph(g); //assegnamo i valori ai vertici ecc..

    addNode(g);

    //(GRAFO,NODO ORIGINE, NODO DESTINAZIONE, PREZZO ARCO, KM );
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
    userTree = uploadUsers(userTree);
    userTree = uploadAdmins(userTree);
    menu();



    return 0;
}



/*menu' piero e gigi*/
void menu() {
    int choice;
    User user = NULL;
    roleChoised = -1;
    char newCity [MAX_WORDS];
    //UserTree userTree = NULL;

    printf("\nSeleziona:\n1 - Login\n2 - Registrazione\n7 - Exit\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            login(userTree,ptrRole);
            break;
        }

        case 2: {
            userTree = insertUserNodeTree(userTree, signIn(userTree));
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
            printf("\nSeleziona:\n1 - Aggiungi Localita'\n2 - Aggiungi tratta\n3 - Visualizza Utenti\n4 - Visualizza Admin\n5 - Upload users\n6 - Upload admins\n7 - Exit\n");
            scanf("%d", &choice);

            switch (choice) {

                case 1: {

                    addNode(g);
                    printf ("- - - - - -\nInserisci il nome della nuova località da aggiungere -> ");
                    //fgets(newCity, MAX_WORDS, stdin);
                    scanf("%s",newCity);
                    setNodeName(g,g->nodes_count -1,newCity);
                    printf("\n\n- - - -\n - - - -\n");
                    printGraphWithNames(g);

                    break;
                }

                case 2: {
                    //appositamente nomi differenti
                    int departure;
                    int destination;
                    int distance;
                    int rate;

                    printGraphWithNames(g);
                    printf("Inserisci il numero relativo alla località di PARTENZA \n-> ");
                    scanf ("%d", &departure);
                    printf("\nInserisci il numero relativo alla località di ARRIVO \n-> ");
                    scanf ("%d", &destination);
                    printf("Inserisci la distanza in km della tratta tra le due località \n-> ");
                    scanf ("%d", &distance);
                    printf("\nInserisci il prezzo di tale tratta \n-> ");
                    scanf ("%d", &rate);
                    addEdge(g,departure,destination,distance,rate);
                    printGraphWithNames(g);

                    break;
                }

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



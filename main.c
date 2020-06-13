#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Graph/graph.h"
#include "List/list.h"
#include "User/user.h"
#include "CheckMail/checkMail.h"
#include "Util/util.h"
//#include "Booking/booking.h"

void menu();
void menuBooking();
void backToMenu();

UserTree userTree = NULL;
ListUserBooking listUserBooking = NULL;
Graph g = NULL ; //allochiamo la memoria per le variabili del grafo
User user = NULL;

int main() {
    char cities[7][50] = {"napoli","milano","berlino","roma","palermo","londra","Catania"};

    //Grafo test inizio
    g = initGraph(6); //allochiamo la memoria per le variabili del grafo

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
    //Grafo test fine
    
    //g = presetGraph(g);
    
    userTree = uploadUsers(userTree);
    userTree = uploadAdmins(userTree);

    user = (User) malloc(sizeof(struct usr));

    menu();

    return 0;
}

void menu() {
    int choice;
    bool loginSuccess = false;
    //roleChoised = -1;
    char newCity [MAX_WORDS];
    //UserTree userTree = NULL;

    printf("\nSeleziona:\n1 - Login\n2 - Registrazione\n7 - Exit\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            loginSuccess = login(userTree, &user);

            if(!loginSuccess) {
                printf("Credenziali non corrette - perfavore riprova!\n");
                menu();
                break;
            }

            printf("Bevenuto %s %s\n", user->name, user->surname);

            menuBooking();

            break;
        }

        case 2: {
            user = signIn(userTree);
            //enqueueListUserBooking(listUserBooking, createUserBooking(user, NULL));
            userTree = insertUserNodeTree(userTree, user);

            menuBooking();

            break;
        }
        case 7: {
            printf("\nArrivederci!");
            return;
        }

        default: {
            printf("Scelta errata - riprova!\n");
            menu();
        }
    }
    
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

void menuBooking() {
    int choice, choiceDestination, departureKey, destinationKey;

    City city = getAllCityFromGraph(g);
    City departure, destination;
    printf("Seleziona la citta' di partenza\n");

    departure = choiceCity(city, "Seleziona la citta' di partenza");
    printf("Hai scelto %s\n", departure->name);

    choiceDestination = choiceBetweenTwo("Vuoi inserire la citta' di destinazione?\nSI = 1\nNO = 2\n");

    departureKey = getKeyVertexFromGraph(g, departure);

    //Punto 1 traccia Progetto
    if(choiceDestination == 1) {
        destination = choiceCity(city, "Seleziona la citta' di destinazione");
        printf("Hai scelto %s\n", destination->name);

        while (cityIsEqual(departure, destination)) {
            printf("\nErrore - la citta' di partenza e destinazione devono essere diverse!\n");
            destination = choiceCity(city, "Seleziona la citta' di destinazione");
        }

        destinationKey = getKeyVertexFromGraph(g, destination);

        //controllo se esiste la tratta
        if(existLinkDfs(g, departureKey, destinationKey) != 1) {
            printf("Errore");
            //esco ed esce menu da stabilire
        }
        else {
            listUserBooking = bookingCheaperOrShortestPath(g, departureKey, destinationKey, listUserBooking, user);
            printf("OK");
        }
    }
    //Punto 2 traccia Progetto
    else {
        choiceDestination = choiceBetweenTwo("\nSeleziona:\n1 - Meta piu' economica\n2 - Meta piu' gettonata\n");

        if(choiceDestination == 1) {
            destinationKey = destinationCheaper(g, departureKey);
        } else {
            destinationKey = destinationMostPopular(g, departureKey);
        }

        listUserBooking = bookingCheaperOrShortestPath(g, departureKey, destinationKey, listUserBooking, user);

    }

    menuBooking();
}


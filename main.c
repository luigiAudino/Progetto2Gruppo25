#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Graph/graph.h"
#include "List/list.h"

#include "CheckMail/checkMail.h"
#include "Util/util.h"


void menu();
void menuBooking();
void menuUser();
void backToMenu();
void menuAdmin();
void wowEffect();

UserTree userTree = NULL;
ListUserBooking listUserBooking = NULL;
Graph g = NULL ;
User user = NULL;

int main() {


    printf("** Gruppo 25 ** Progetto 2 **\n");
    printf("- - - - - - - - - - - - - - -\n");
    printf("** Giuliano Galloppi - N86001508 **\n");
    printf("** Piero Junior Gaetani - N86002210 **\n");
    printf("** Luigi Audino - N86001513 **\n");
    printf("- - - - - - - - - - - - - - -\n");

    g = presetGraph(g);//Pre-caricamento del grafo coi nodi e con gli archi.

    //Presettaggio di utenti ed amministratori
    userTree = uploadUsers(userTree);
    userTree = uploadAdmins(userTree);

    user = (User) malloc(sizeof(struct usr));

    menu();
    return 0;
}









void menu() {
    int choice;
    bool loginSuccess = false;
    char newCity [MAX_WORDS];

    printf("\nSeleziona:\n1 - Login\n2 - Registrazione\n3 - Exit\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            loginSuccess = login(userTree, &user);
            if(!loginSuccess) {
                printf("Credenziali non corrette - perfavore riprova!\n");
                menu();
                break;
            }

            printf("\nBenvenuto\n");

            if (strcmp(user->role, USER) == 0) {
                menuUser();
            }else {
                menuAdmin();
            }

            break;
        }

        case 2: {
            user = signIn(userTree);
            userTree = insertUserNodeTree(userTree, user);
            menuUser();
            break;
        }
        case 3: {
            wowEffect();
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
}



void menuUser() {
    int choice = choiceBetweenN("\nMENU' UTENTE:\nSeleziona:\n1 - Effettua nuova prenotazione\n2 - Visualizza prenotazioni\n3 - Visualizza punti sconto accumulati\n4 - Exit\n", 4);

    while(choice!=4){

    switch (choice) {
        case 1: {
            menuBooking();
            break;
        }
        case 2: {
            printBooking(user, listUserBooking);
            break;
        }
        case 3: {
            printf("%d punti accumulati\n", user->points);
            break;
        }
        case 4: {
            return;
        }
        default: {
            printf("Scelta errata - riprova!\n");
            }
        }
        choice = choiceBetweenN("\nSeleziona:\n1 - Effettua nuova prenotazione\n2 - Visualizza prenotazioni\n3 - Visualizza punti sconto accumulati\n4 - Exit\n", 4);
    }
    printf("\nArrivederci!");
}




void menuBooking() {
    int choice, choiceDestination, departureKey, destinationKey, priceOfPurchase, confirmOperation, confirmUseOfPoints, addNewPoints;

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
            printf("ERRORE: La tratta non esiste\n");
        }
        else {
            //Qui avviene il procedimento di scelta delle tratte e eventuale conferma della prenotazione
            listUserBooking = bookingCheaperOrShortestPath(g, departureKey, destinationKey, listUserBooking, user);
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
            listUserBooking = bookingCheaperOrShortestPath(g, departureKey, destinationKey, listUserBooking, user);}
    }




void menuAdmin() {
    //ADMIN
    int choice;
    char newCity[MAX_WORDS];
    printf("\nMENU' ADMIN\nSeleziona:\n1 - Aggiungi Citta'\n2 - Rimuovi Citta'\n3 - Aggiungi tratta\n4 - Rimuovi tratta tra due Citta'\n5 - Stampa grafo\n---opzionali---\n6 - Visualizza Utenti\n7 - Visualizza Admin\n8 - Exit\n");
    scanf("%d", &choice);

    switch (choice) {

        case 1: {
            int pointOfCity;

            addNode(g);
            printf("\nInserisci il nome della nuova citta' da aggiungere -> ");
            scanf("%s", newCity);
            setNodeName(g, g->nodes_count - 1, newCity);
            printf("inserisci punteggio citta' gettonata: ");
            scanf("%d",&pointOfCity);
            setNodeCityPopularPoints(g,g->nodes_count-1,pointOfCity);
            printf("\nNuovo grafo attuale:\n");
            printGraphWithNames(g);

            break;
        }

        case 2: {
            int nodeToBeDeleted;
            printGraphIndexNameAndPoints(g);

            printf("\nInserisci il numero corrispondente della citta' da rimuovere: ");
            scanf("%d", &nodeToBeDeleted);
            removeNode(g, nodeToBeDeleted);

            printf("\nNuovo grafo attuale:\n");
            printGraphIndexNameAndPoints(g);

            break;
        }

        case 3: {

            int departure;
            int destination;
            int distance;
            int rate;

            printGraphIndexNameAndPoints(g);
            printf("Inserisci il numero relativo alla citta' di PARTENZA \n-> ");
            scanf("%d", &departure);
            printf("\nInserisci il numero relativo alla citta' di ARRIVO \n-> ");
            scanf("%d", &destination);
            printf("Inserisci la distanza in km della tratta tra le due citta' \n-> ");
            scanf("%d", &distance);
            printf("\nInserisci il prezzo di tale tratta \n-> ");
            scanf("%d", &rate);
            addEdge(g, departure, destination, distance, rate);

            printf("\nNuovo grafo attuale:\n");
            printGraphWithNames(g);

            break;
        }

        case 4: {
            int archDepartureToBeDeleted;
            int archDestinationToBeDeleted;

            printGraphWithNames(g);
            printf("\nInserisci il numero corrispondente della citta' di PARTENZA della tratta da rimuovere -> ");
            scanf("%d", &archDepartureToBeDeleted);
            printf("\n");
            printf("\nInserisci il numero corrispondente della citta' di ARRIVO della tratta da rimuovere -> ");
            scanf("%d", &archDestinationToBeDeleted);
            printf("\n");
            removeEdge(g, archDepartureToBeDeleted, archDestinationToBeDeleted);

            printf("\nNuovo grafo attuale:\n");
            printGraphWithNames(g);

            break;
        }

        case 5: {
            printGraphWithNames(g);
            break;
        }

        case 6: {
            if (countUser(userTree) == 0)
                printf("Non e' presente alcun user!\n");
            else
                getAllUserPrint(userTree);

            break;
        }

        case 7: {
            if (countAdmin(userTree) == 0)
                printf("Non e' presente alcun admin!\n");
            else
                getAllAdminPrint(userTree);

            break;
        }


        case 8: {
            printf("\nArrivederci!");
            return;
        }

        default: {
            printf("Scelta errata - riprova!\n");
            break;
        }
    }
    backToMenu();
}


void wowEffect(){
    printf("                   ()\n"
           "                 __/\\__         \n"
           "        |\\   .-\"`      `\"-.   /|\n"
           "        | \\.'( ') (' ) (. )`./ |\n"
           "         \\_                  _/\n"
           "           \\  `~\"'=::='\"~`  /\n"
           "    ,       `-.__      __.-'       ,\n"
           ".---'\\________( `\"\"~~\"\"` )________/'---.\n"
           " >   )       / `\"\"~~~~\"\"` \\       (   <\n"
           "'----`--..__/        -(-)- \\__..--`----'\n"
           "            |_____ __ _____|\n"
           "            [_____[##]_____]  I HAVE BEEN CHOSEN...\n"
           "            |              |    FAREWELL MY FRIENDS...\n"
           "            \\      ||      /     I GO ONTO A BETTER PLACE!\n"
           "             \\     ||     /\n"
           "          .-\"~`--._||_.--'~\"-.\n"
           "         (_____,.--\"\"--.,_____)\n\n");

    printf("            _._                           _._\n"
           "           ||||                           ||||\n"
           "           ||||_           ___           _||||\n"
           "           |  ||        .-'___`-.        ||  |\n"
           "           \\   /      .' .'_ _'. '.      \\   /\n"
           "           /~~|       | (| b d |) |       |~~\\\n"
           "          /'  |       |  |  '  |  |       |  `\\\n"
           ",        /__.-:      ,|  | `-' |  |,      :-.__\\       ,\n"
           "|'-------(    \\-''\"\"/.|  /\\___/\\  |.\\\"\"''-/    )------'|\n"
           "|         \\_.-'\\   /   '-._____.-'   \\   /'-._/        |\n"
           "|.---------\\   /'._| _    .---. ===  |_.'\\   /--------.|\n"
           "'           \\ /  | |\\_\\ _ \\=v=/  _   | |  \\ /          '\n"
           "             `.  | | \\_\\_\\ ~~~  (_)  | |  .'\n"
           "               `'\"'|`'--.__.^.__.--'`|'\"'`\n"
           "                   \\                 /\n"
           "                    `,..---'\"'---..,'\n"
           "                      :--..___..--:    TO INFINITY...\n"
           "                       \\         /  \n"
           "                       |`.     .'|       AND BEYOND!\n"
           "                       |  :___:  |\n"
           "                       |   | |   |\n"
           "                       |   | |   |\n"
           "                       |.-.| |.-.|\n"
           "                       |`-'| |`-'|\n"
           "                       |   | |   |\n"
           "                      /    | |    \\\n"
           "                     |_____| |_____|\n"
           "                     ':---:-'-:---:'\n"
           "                     /    |   |    \\\n"
           "                    /.---.|   |.---.\\\n"
           "                    `.____;   :____.'\n\n");

    printf("           .-'\"\"\"'-.\n"
           "      ,____|_______|____,\n"
           "       '._____________.'  REACH FOR\n"
           "           |.-- --.|      THE SKY!\n"
           "           |(o) (o)|\n"
           "          (|       |)\n"
           "           |   U   |\n"
           " __        | .___. |    YOU'RE MY \n"
           "/|||       |       |     FAVORITE\n"
           "||||       :       :      DEPUTY!\n"
           "|  |/)      `.___.'\n"
           " \\  /       __) (__\n"
           "  \\/\\      /\\ \\ / /\\\n"
           "   \\ \\    /\\ \\ ^ / /\\    THERE'S A\n"
           "    \\ \\  / |  |0_/\\_ \\    SNAKE IN\n"
           "     \\ \\/ /|  | \\  /\\ \\    MY BOOT!\n"
           "      \\  / |  |0//\\\\ \\ \\\n"
           "       \\/  | /   \\ |  \\ \\\n"
           "           |/ .-. \\|  / /\n"
           "        .-'|-( ~ )-| / /   HI!\n"
           "        \\  |--`-'--|/ /   MY NAME'S WOODY!\n"
           "         \\ |       | /\n"
           "          \\|   |   |/\n"
           "           |   |   |\n"
           "           |   |   |     HOWDY PARDNER!\n"
           "           |   |   |\n"
           "           |   |   |\n"
           "           |   |   |\n"
           "           |___|___|     YEEEHAH COWBOY!\n"
           "          `|---|---|'\n"
           "          *|   |   |*\n"
           "           |_._|_._|\n"
           "          /'  /|\\  '\\    SOMEONE POISONED\n"
           "         /   /^ ^\\   \\    THE WATERHOLE!\n"
           "        /__.'     `.__\\\n\n");

    printf("- - - - - - - - - - - - - - -\n");
    printf("** Gruppo 25 ** Progetto 2 **\n");
    printf("- - - - - - - - - - - - - - -\n");
    printf("** Giuliano Galloppi - N86001508 **\n");
    printf("** Piero Junior Gaetani - N86002210 **\n");
    printf("** Luigi Audino - N86001513 **\n");
    printf("- - - - - - - - - - - - - - -\n");
}
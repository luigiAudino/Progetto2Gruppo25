

/*Gruppo 25 - Progetto 2 - Giuliano Galloppi N86001508; Piero Junior Gaetani N86002210; Luigi Audino N86001513*/

#ifndef PROGETTO2GRUPPO25_BOOKING_H
#define PROGETTO2GRUPPO25_BOOKING_H

#endif //PROGETTO2GRUPPO25_BOOKING_H

#include "../User/user.h"

struct city {
    char name[MAX_WORDS];
    struct city *next;
};

typedef struct city *City;

struct booking {
    City city;
    int price;
    struct booking *next;
};

typedef struct booking *Booking;

struct userBooking {
    User user;
    Booking booking;
};

typedef struct userBooking *UserBooking;

struct listUserBooking {
    UserBooking userBooking;
    struct listUserBooking *next;
};

typedef struct listUserBooking *ListUserBooking;

//Istanzia struttura prenotazione (Un booking per ogni user)
Booking createBooking(int price, City city);

Booking enqueueBooking(Booking booking, int price, City city);

//InCoda una citta'
City enqueueCity(City cities, char *nameCity);

//Decoda una citta'
City dequeueCity(City city);

//Aggiunge una prenotazione
Booking addBooking(Booking booking, char *nameCity);

//Rimuove l'ultima prenotazione, ovvero quella più vecchia
Booking removeLastBooking(Booking booking, char *nameCity);

//Stampa tutte le citta'
void printCity(City city);

City choiceCity(City city, char *message);

//Confronta due citta' ed in base al fatto che siano uguali o meno restituiisce un valore booleano
bool cityIsEqual(City city1, City city2);

UserBooking createUserBooking(User user, Booking booking);

UserBooking addBookingToUserBooking(UserBooking userBooking, User user, Booking booking);

ListUserBooking createListUserBooking(UserBooking userBooking);

ListUserBooking enqueueListUserBooking(ListUserBooking listUserBooking, UserBooking userBooking);

//Ritorna la prima citta' della lista in ingresso
char* getDepartureCity(City cities);

//Ritorna l'ultima citta' della lista in ingresso
char* getDestinationCity(City cities);

//Carica una lista di users
UserTree uploadUsers(UserTree userTree);

//Otteniamo lo userBooking che desideriamo dallo user cercando nella lista contenente tutti gli userBooking, altrimenti null
UserBooking getUserBookingFromListUserBooking(ListUserBooking listUserBooking, User user);

void printBooking(User user, ListUserBooking listUserBooking);

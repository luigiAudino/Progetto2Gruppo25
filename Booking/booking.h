//
// Created by Luigi Audino on 06/06/2020.
//

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
    float price;
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
Booking createBooking(int price, char *nameCity);

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
void printBooking(City city);

City choiceCity(City city, char *message);

bool cityIsEqual(City city1, City city2);

UserBooking createUserBooking(User user, Booking booking);

void enqueueUserBooking(UserBooking userBooking, int price, City city);

ListUserBooking createListUserBooking(UserBooking userBooking);

ListUserBooking enqueueListUserBooking(ListUserBooking listUserBooking, UserBooking userBooking);

//Ritorna la prima citta' della lista in ingresso
char* getDepartureCity(City cities);

//Ritorna l'ultima citta' della lista in ingresso
char* getDestinationCity(City cities);

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
    User user;
    //TODO List<City>
    City city;
};

typedef struct booking *Booking;

//Istanzia struttura prenotazione (Un booking per ogni user)
Booking createBooking(User user, char *nameCity);

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

//
// Created by Luigi Audino on 06/06/2020.
//

#include "booking.h"

Booking createBooking(User user, char *nameCity) {
    Booking booking = (Booking) malloc(sizeof(struct booking));

    booking->user = user;

    booking->city = (City) malloc(sizeof(struct city));
    strcpy(booking->city->name, nameCity);
    booking->city->next = NULL;

    return booking;
}

City enqueueCity(City cities, char *nameCity) {
    if (cities != NULL) {
        if (cities->next == NULL) {
            City newCity = (City) malloc(sizeof(struct city));
            cities->next = newCity;
            strcpy(newCity->name, nameCity);
            newCity->next = NULL;
        } else
            enqueueCity(cities->next, nameCity);
    } else {
        cities = (City)malloc(sizeof(struct city));
        strcpy(cities->name, nameCity);
        cities->next = NULL;
    }

    return cities;
}

City dequeueCity(City city) {
    if (city == NULL)
        return NULL;
    else {
        city = city->next;
    }

    return city;
}

Booking addBooking(Booking booking, char *nameCity) {
    if (booking != NULL) {
        enqueueCity(booking->city, nameCity);
    } else
        booking = createBooking(booking->user, nameCity);

    return booking;
}

Booking removeLastBooking(Booking booking, char *nameCity) {
    if (booking != NULL) {
        booking->city = dequeueCity(booking->city);
    }

    return booking;
}

void printBooking(City city) {
    if (city != NULL) {
        printf("\nPrenotazione: %s\n", city->name);
        printBooking(city->next);
    }
}
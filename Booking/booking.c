//
// Created by Luigi Audino on 06/06/2020.
//

#include "booking.h"

Booking createBooking(int price, City city) {
    Booking booking = (Booking) malloc(sizeof(struct booking));

    booking->city = city;
    booking->price = price;

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
        cities = (City) malloc(sizeof(struct city));
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

/*
Booking addBooking(Booking booking, char *nameCity) {
    if (booking != NULL) {
        enqueueCity(booking->city, nameCity);
    } else
        booking = createBooking(nameCity);

    return booking;
}*/

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

City choiceCity(City city, char *message) {
    int i = 0, choice;
    bool isRight = true, foundIt = false;
    City cityReturned = NULL;
    City head = city;

    while (city != NULL) {
        i++;
        printf("%d: %s\n", i, city->name);
        city = city->next;
    }

    do {
        if (!isRight)
            printf("Scelta errata, per favore riprova!\n");

        printf("%s\n", message);
        //fflush(stdin);
        scanf("%d", &choice);

        isRight = false;
    } while (choice < 1 || choice > i);

    i = 1;
    while (head != NULL) {
        if(i == choice) {
            cityReturned = head;
            break;
        }
        head = head->next;
        i++;
    }

    return cityReturned;
}

bool cityIsEqual(City city1, City city2) {
    return city1->name == city2->name;
}

UserBooking createUserBooking(User user, Booking booking) {
    UserBooking userBooking = (UserBooking) malloc(sizeof(struct userBooking));
    if(user == NULL)
        user = (User) malloc(sizeof( struct usr));

    //if(booking == NULL)
    //booking = (Booking) malloc(sizeof(struct booking));

    userBooking->user = user;
    userBooking->booking = booking;

    return userBooking;
}

Booking enqueueBooking(Booking booking, int price, City city) {
    if(booking == NULL) {
        return createBooking(price, city);
    }

    Booking newBooking = (Booking) malloc(sizeof( struct booking));

    if(city == NULL)
        return newBooking;

    strcpy(newBooking->city->name, city->name);
    newBooking->price = price;
    newBooking->next = NULL;

    Booking head = booking;

    while (booking->next != NULL) {
        booking = booking->next;
    }

    booking->next = newBooking;

    return head;
}

UserBooking enqueueUserBooking(UserBooking userBooking, Booking booking) {
    UserBooking head = userBooking;

    if(userBooking == NULL) {
        return createUserBooking(userBooking->user, booking);
    }

    while (userBooking->booking->next != NULL) {
        userBooking->booking = userBooking->booking->next;
    }

    userBooking->booking->next = booking;

    return head;
}

ListUserBooking createListUserBooking(UserBooking userBooking) {
    ListUserBooking listUserBooking = (ListUserBooking) malloc(sizeof(struct listUserBooking));
    listUserBooking->userBooking = userBooking;

    return listUserBooking;
}

ListUserBooking enqueueListUserBooking(ListUserBooking listUserBooking, UserBooking userBooking) {
    ListUserBooking head = listUserBooking;

    if(listUserBooking == NULL) {
        return createListUserBooking(userBooking);
    }

    while (listUserBooking->next != NULL) {
        listUserBooking = listUserBooking->next;
    }

    ListUserBooking listUserBookingNew = (ListUserBooking)malloc(sizeof(struct listUserBooking));
    listUserBookingNew->userBooking = userBooking;

    listUserBooking->next = listUserBookingNew;

    return head;
}

char* getDepartureCity(City cities){
    if (cities!=NULL){
        return cities->name;
    }

    return NULL;
}

char* getDestinationCity(City cities){
    if (cities!=NULL){
        while(cities->next!=NULL){
            cities = cities->next;
        }
    }
    return cities->name;
}


UserTree uploadUsers(ListUserBooking  listUserBooking, UserTree userTree) {
    char names[6][MAX_WORDS] = {"Luigi", "Piero Junior", "Giulio", "Annabella", "Andrea", "Silvia"};
    char surnames[6][MAX_WORDS] = {"Audino", "Gaetani", "Galloppi", "Calabrese", "Audino", "Stranieri"};
    char emails[6][MAX_WORDS] = {"luigi@mail.it", "piero@mail.it", "giulio@mail.it", "annabella@mail.it",
                                 "andrea@mail.it", "silvia@mail.it"};

    for (int i = 0; i < 6; i++) {
        User user = (User) malloc(sizeof(struct usr));

        strcpy(user->role, USER);
        strcpy(user->name, names[i]);
        strcpy(user->surname, surnames[i]);
        strcpy(user->email, emails[i]);
        strcpy(user->password, "123");

        userTree = insertUserNodeTree(userTree, user);

        createUserBooking(user, NULL);

        UserBooking userBooking = createUserBooking(user, NULL);
        listUserBooking = enqueueListUserBooking(listUserBooking, userBooking);
    }

    return userTree;
}


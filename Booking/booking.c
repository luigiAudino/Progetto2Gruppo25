//
// Created by Piero Junior Gaetani on 14/06/2020.
//

#include "booking.h"

Booking createBooking(int price, City city) {
    Booking booking = (Booking) malloc(sizeof(struct booking));

    booking->city = city;
    booking->price = price;
    booking->next = NULL;

    return booking;
}

City enqueueCity(City cities, char *nameCity) {
    if (cities != NULL) {
        if (cities->next == NULL) {
            City newCity = (City) malloc(sizeof(struct city));

            strcpy(newCity->name, nameCity);
            newCity->next = NULL;

            cities->next = newCity;
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

Booking removeLastBooking(Booking booking, char *nameCity) {
    if (booking != NULL) {
        booking->city = dequeueCity(booking->city);
    }

    return booking;
}

// Stampa nomi citta'
void printCity(City city) {
    if (city != NULL) {
        printf("%s ", city->name);

        if(city->next!=NULL){
            printf(" - ");
        }else{
            printf("\n");
        }

        printCity(city->next);
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
        if (i == choice) {
            cityReturned = head;
            break;
        }
        head = head->next;
        i++;
    }

    return cityReturned;
}

//Confronta due citta' ed in base al fatto che siano uguali o meno restituiisce un valore booleano
bool cityIsEqual(City city1, City city2) {
    return city1->name == city2->name;
}

UserBooking createUserBooking(User user, Booking booking) {
    UserBooking userBooking = (UserBooking) malloc(sizeof(struct userBooking));

    userBooking->user = user;
    userBooking->booking = booking;
    //userBooking->booking->next = NULL;

    return userBooking;
}

Booking enqueueBooking(Booking booking, int price, City city) {
    if (booking == NULL) {
        return createBooking(price, city);
    }

    Booking newBooking = (Booking) malloc(sizeof(struct booking));

    if (city == NULL)
        return newBooking;

    newBooking->city = city;
    newBooking->price = price;
    newBooking->next = NULL;

    Booking head = booking;

    while (booking->next != NULL) {
        booking = booking->next;
    }

    booking->next = newBooking;

    return head;
}

//Aggiunge all'utente delle prenotazioni
UserBooking addBookingToUserBooking(UserBooking userBooking, User user, Booking booking) {
    UserBooking head = userBooking;
    Booking prec;

    if (userBooking == NULL) {
        return createUserBooking(user, booking);
    }

    Booking b = userBooking->booking;

    while (b != NULL) {
        prec = b;
        b = b->next;
    }

    prec->next = booking;

    return head;
}

UserBooking getUserBookingFromListUserBooking(ListUserBooking listUserBooking, User user) {
    UserBooking userBooking = NULL;
    if (listUserBooking != NULL) {
        while (listUserBooking->userBooking != NULL) {
            if (userEquals(listUserBooking->userBooking->user, user)) {
                userBooking = listUserBooking->userBooking;
                break;
            }

            listUserBooking = listUserBooking->next;
        }
    }

    return userBooking;
}

ListUserBooking createListUserBooking(UserBooking userBooking) {
    ListUserBooking listUserBooking = (ListUserBooking) malloc(sizeof(struct listUserBooking));

    listUserBooking->userBooking = userBooking;
    listUserBooking->next = NULL;

    return listUserBooking;
}

ListUserBooking enqueueListUserBooking(ListUserBooking listUserBooking, UserBooking userBooking) {
    bool foundIt = false;

    ListUserBooking head = listUserBooking;
    ListUserBooking prec;

    if (listUserBooking == NULL) { // || listUserBooking->userBooking == NULL) {
        return createListUserBooking(userBooking);
    }

    while (listUserBooking != NULL) {
        if (userEquals(listUserBooking->userBooking->user, userBooking->user) == true) {
            foundIt = true;

            listUserBooking->userBooking = userBooking;

            break;
        } else {

            prec = listUserBooking;
            listUserBooking = listUserBooking->next;
        }
    }

    if (!foundIt) {
        ListUserBooking listUserBookingNew = (ListUserBooking) malloc(sizeof(struct listUserBooking));
        listUserBookingNew->userBooking = userBooking;
        listUserBookingNew->next = NULL;

        prec->next = listUserBookingNew;
    }

    return head;
}

char *getDepartureCity(City cities) {
    if (cities != NULL) {
        return cities->name;
    }

    return NULL;
}

char *getDestinationCity(City cities) {
    if (cities != NULL) {
        while (cities->next != NULL) {
            cities = cities->next;
        }
    }
    return cities->name;
}


UserTree uploadUsers(UserTree userTree) {
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
        user->points = 10;

        userTree = insertUserNodeTree(userTree, user);
    }

    return userTree;
}

void printBooking(User user, ListUserBooking listUserBooking) {
    if (listUserBooking != NULL) {
        UserBooking userBookingAssociato = getUserBookingFromListUserBooking(listUserBooking, user);

        if (userBookingAssociato != NULL) {
            int i = 0;
            Booking booking = userBookingAssociato->booking;

            while (booking != NULL) {
                City listaCityAssociataAlBooking = booking->city;
                printf("Prenotazione %d - Da %s A %s\nTratta: ",i+1,getDepartureCity(listaCityAssociataAlBooking),getDestinationCity(listaCityAssociataAlBooking));                printCity(listaCityAssociataAlBooking);
                booking = booking->next;
                i++;
            }

        } else
            puts("Non hai effettuato alcuna prenotazione\n");
    } else {
        puts("Non hai effettuato alcuna prenotazione\n");
        //la listUserBooing e' NULL
    }
}

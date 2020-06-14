#include<ctype.h>
#include<string.h>
#include <stdbool.h>
#include "stdio.h"
#include"util.h"

/*Gruppo 25 - Progetto 2 - Giuliano Galloppi N86001508; Piero Junior Gaetani N86002210; Luigi Audino N86001513*/

void strtolower(char input[] , char output[]){ // converte la stringa di input in caratteri minuscoli nella stringa di output;
    int i = 0;
    while(input[i]!='\0'){
        output[i] = tolower(input[i]);
        i += 1;
    }
    output[i]='\0';
}

int choiceBetweenTwo(char *message) {
    bool isRight = true;
    int choice;
    do {
        if (!isRight)
            printf("Scelta errata, per favore riprova!\n");

        printf("%s\n", message);
        scanf("%d", &choice);

        isRight = false;
    } while (choice != 1 && choice != 2);

    return choice;
}

int choiceBetweenN(char *message, int num) {
    bool isRight = true;
    int choice;
    do {
        if (!isRight)
            printf("Scelta errata, per favore riprova!\n");

        printf("%s\n", message);
        scanf("%d", &choice);

        isRight = false;
    } while (choice < 1 || choice > num);

    return choice;
}

#include<ctype.h>
#include<string.h>
#include <stdbool.h>
#include "stdio.h"
#include"util.h"

void strtolower(char input[] , char output[]){ // converte la stringa di input in caratteri minuscoli nella stringa di output;
    int i = 0;
    while(input[i]!='\0'){
        output[i] = tolower(input[i]);
        //printf("output %c - input %c\n",output[i],input[i]);
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

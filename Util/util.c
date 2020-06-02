#include<ctype.h>
#include<string.h>
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

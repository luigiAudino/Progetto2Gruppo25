#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

/*Gruppo 25 - Progetto 2 - Giuliano Galloppi N86001508; Piero Junior Gaetani N86002210; Luigi Audino N86001513*/


List appendNodeList(List L, int target, int price, int km) {
    if (L != NULL) {
        if (L->target != target) {
            L->next = appendNodeList(L->next, target, price, km);
        }
    } else {
        L = initNodeList(target, price, km);
    }
    return L;
}

List removeNodeList(List L, int target) {
    if (L != NULL) {
        if (L->target == target) {
            List tmp = L->next;
            free(L);
            return tmp;
        }
        L->next = removeNodeList(L->next, target);
    }
    return L;
}

List initNodeList(int target, int price, int km) {
    List L = (List)malloc(sizeof(struct TList));
    L->target = target;
    L->price = price;
    L->km = km;
    L->next = NULL;
    return L;
}





/*
List addNodeList(List L, int target, int peso) {
    if (L != NULL) {
        List G = (List )malloc(sizeof(struct TList));
        G->target = target;
        G->next = L;
        return G;
    }
    return initNodeList(target, peso);
}*/


void freeList(List L) {
    if (L != NULL) {
        freeList(L->next);
        free(L);
    }
}


void printList(List L) {
    if (L != NULL) {
        printf(" [Destinazione: %d  prezzo: %d  km: %d] , ", L->target, L->price, L->km);
        printList(L->next);
    }
}

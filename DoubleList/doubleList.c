#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../DoubleList/doubleList.h"

List initNodeDoubleList(int info, int peso) {
    List L = (List)malloc(sizeof(struct TList));
    L->target = info;
    L->peso = peso;
    L->next = NULL;
    L->prev = NULL;
    return L;
}


List randomDoubleList(int index, int mod) {
    srand((unsigned int)time(NULL));
    List L = NULL;
    int i = 0;
    for (i = 0; i < index; i++) {
        L = appendNodeDoubleList(L, rand() % mod, rand() % 50);
    }
    return L;
}


List appendNodeDoubleList(List L, int target, int peso) {
    if (L != NULL) {
        if (L->target != target) {
            L->next = appendNodeDoubleList(L->next, target, peso);
            L->next->prev = L;
        }
    } else {
        L = initNodeDoubleList(target, peso);
    }
    return L;
}

List addNodeDoubleList(List L, int target, int peso) {
    if (L != NULL) {
        List G = (List )malloc(sizeof(struct TList));
        G->target = target;
        G->next = L;
        G->next->prev = G;
        G->prev = NULL;
        return G;
    }
    return initNodeDoubleList(target, peso);
}




List removeNodeDoubleList(List L, int target) {
    if (L != NULL) {
        if (L->target == target) {
            List tmp = L->next;
            tmp->prev = L->prev;
            free(L);
            return tmp;
        }
        L->next = removeNodeDoubleList(L->next, target);
    }
    return L;
}


void freeDoubleList(List L) {
    if (L != NULL) {
        freeDoubleList(L->next);
        free(L);
    }
}


void printDoubleList(List L) {
    if (L != NULL) {

        if((L->prev != NULL) && (L->next != NULL)) {
            printf("| (%d) %d (%d) |", L->prev->target, L->target, L->next->target);
            printDoubleList(L->next);
        } else {
            if((L->prev == NULL) && (L->next == NULL)) {
                printf("| (NULL) %d (NULL) |",L->target);
                printDoubleList(L->next);
            } else {
                if(L->prev == NULL) {
                    printf("| (NULL) %d (%d) |", L->target, L->next->target);
                    printDoubleList(L->next);
                } else {
                    printf("| (%d) %d (NULL) |", L->prev->target, L->target);
                    printDoubleList(L->next);
                }
            }
        }

    }
}

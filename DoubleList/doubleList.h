#ifndef Graph_List_h
#define Graph_List_h

struct TList {
    int target;
    int peso;
    struct TList* next;
    struct TList* prev;
};

typedef struct TList* List;

// Inizializza un nuovo nodo
List initNodeDoubleList(int info, int peso);

// Crea una lista random, per mod si
// puo' specificare il modulo utilizzato la funzione rand()
// La funzione ritorna sempre la testa della lista
List randomDoubleList(int index, int mod);

// Aggiunge un nodo alla fine della lista
// controllandone l'esistenza
// La funzione ritorna sempre la testa della lista
List appendNodeDoubleList(List L, int target, int peso);

// Aggiunge un nodo in testa alla lista
// senza controllare l'esistenza
// La funzione ritorna sempre la testa della lista
List addNodeDoubleList(List L, int target, int peso);

// Rimuove solo un occorrenza di un nodo con il target specificato
// dalla lista
// La funzione ritorna sempre la testa della lista
List removeNodeDoubleList(List L, int target);

// Dealloca la lista interamente
void freeDoubleList(List L);

// Stampa la lista
void printDoubleList(List L);
#endif

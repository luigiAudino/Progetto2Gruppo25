#ifndef Graph_List_h
#define Graph_List_h

//Lista = Arco
struct TList {
    int target; //città del nodo
    int price; //peso1
    int km; //peso2
    struct TList* next; //prossimo vertice nella di adiacenza del vertice 'x'
};

typedef struct TList* List;

// Aggiunge un nodo alla fine della lista
// controllandone l'esistenza
// La funzione ritorna sempre la testa della lista
List appendNodeList(List L, int target, int price, int km); //aggiunge un vertice 'taget' alla lista L del vertice d'origine designato

// Rimuove solo un occorrenza di un nodo con il target specificato dalla lista
// La funzione ritorna sempre la testa della lista
List removeNodeList(List L, int target); //Rimuove il nodo con vertice 'target' dalla lista del vertice L che vogliamo

// Inizializza un nuovo nodo
List initNodeList(int target, int price, int km);





// Dealloca la lista interamente
void freeList(List L);

// Stampa la lista
void printList(List L);
#endif

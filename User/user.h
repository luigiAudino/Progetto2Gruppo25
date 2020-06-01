#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "stdio.h"
#include "../BST/tree.h"

#define MAX_WORDS 256
#define USER "user"
#define ADMIN "admin"

struct usr {
    char name[MAX_WORDS];
    char surname[MAX_WORDS];
    char email[MAX_WORDS];
    char password[MAX_WORDS];
    char role[MAX_WORDS];
};

typedef struct usr* User;

struct TTreeUser {
    User user;
    struct TTreeUser* sx;
    struct TTreeUser* dx;
};

typedef struct TTreeUser* UserTree;

//Login
void login(UserTree userTree);

//Registrazione
User signIn(UserTree userTree);

//Stampa a video lo user / admin
void printUser(User user);

//Controlla se lo user / admin è presente nella lista degli users / admins
bool search(UserTree userTree, User user);

//Controlla se due user o admin sono uguali
bool userEquals(User u1, User u2);

//Controlla se l'adimn è presente nella lista degli admins
bool  searchAdmin(UserTree userTree, User user);

//Controlla se lo user è presente nella lista degli users
bool searchUser(UserTree userTree, User user);

//Stampa a video tutti gli users
void getAllUserPrint(UserTree T);

//Stampa a video tutti gli admins
void getAllAdminPrint(UserTree T);

// Inizializza un nuovo nodo user
UserTree initUserNode(User user);

// Inserisce un nodo user nell'albero BST
UserTree insertUserNodeTree(UserTree T, User user);

//Controlla se la lista degli utenti è vuota
bool isEmptyUserTree(UserTree tree);

// Esegue una stampa in Post Order sull'albero UserTree
void postOrderUserTreePrint(UserTree T);

// Esegue una stampa in Pre Order sull'albero UserTree
void preOrderUserTreePrint(UserTree T);

// Esegue una stampa In Order sull'albero UserTree
void inOrderUserTreePrint(UserTree T);

// Esegue un cammino in Post Order sull'albero UserTree
void postOrderUserTree(UserTree T);

// Esegue un cammino in Pre Order sull'albero UserTree
void preOrderUserTree(UserTree T);

// Esegue un cammino In Order sull'albero UserTree
void inOrderUserTree(UserTree T);

//Cancella tutti gli utenti e admin
void freeUserTree(UserTree T);

//Ritorna il numero di admin
int countAdmin(UserTree userTree);

//Ritorna il numero di utenti
int countUser(UserTree userTree);

//Controlla se la mail è stata già scelta
bool emailIsPresent(UserTree userTree, User user);

//Controlla se è già presente un user con la mail inserita
bool emailUserIsPresent(UserTree userTree, char * email);

//Controlla se è già presente un admin con la mail inserita
bool emailAdminIsPresent(UserTree userTree, char * email);

//Carica una lista di users
UserTree uploadUsers(UserTree userTree);

//Carica una lista di admins
UserTree uploadAdmins(UserTree userTree);
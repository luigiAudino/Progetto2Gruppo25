#include "user.h"
#include "../CheckMail/checkMail.h"

User signIn(UserTree userTree) {
    int roleChoised;
    bool isRight = true, isPresent = false;
    char confirmPassword[MAX_WORDS];
    int checkMailRes = -1;

    User user = (User) malloc(sizeof(struct usr));

    do {
        if (!isRight)
            printf("Scelta errata, per favore riprova!\n");

        printf("Seleziona ruolo:\n1 - User\n2 - Admin\n");
        fflush(stdin);
        scanf("%d", &roleChoised);

        isRight = false;
    } while (roleChoised != 1 && roleChoised != 2);

    if (roleChoised == 1)
        strcpy(user->role, "user");
    else
        strcpy(user->role, "admin");

    printf("Inserisci nome\n");
    fflush(stdin);
    fgets(user->name, MAX_WORDS, stdin);
    strtok(user->name, "\n");

    printf("Inserisci cognome\n");
    fflush(stdin);
    scanf("%s", user->surname);

    isRight = true;

    do {
        if (!isRight)
            if (checkMailRes == 1) {
                printf("Esiste già un %s registrato con %s\n", user->role, user->email);
            } if (checkMailRes == 0){
            printf("La mail inserita non è accettabile a causa di caratteri non idonei\n");
        }

        printf("Inserisci email\n");
        fflush(stdin);
        scanf("%s", user->email);

        isPresent = emailIsPresent(userTree, user);
        checkMailRes = isEmail(user->email);

        isRight = false;
    } while (isPresent || checkMailRes == 0);

    isRight = true;

    do {
        if (!isRight)
            printf("Le password non coincidono, per favore riprova!\n");

        printf("Inserisci password\n");
        fflush(stdin);
        scanf("%s", user->password);

        printf("Inserisci nuovamente la password\n");
        fflush(stdin);
        scanf("%s", confirmPassword);

        isRight = false;
    } while (strcmp(user->password, confirmPassword) != 0);

    //printUser(user);

    return user;
}

void printUser(User user) {
    printf("Nome: %s\nCognome: %s\nEmail: %s\nPassword: %s\nRuolo: %s\n", user->name, user->surname, user->email,
           user->password, user->role);
    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");
}

bool login(UserTree userTree, User *user) {
    bool isRight = true, foundIt = false;
    int roleChoised;

    do {
        if (!isRight)
            printf("Scelta errata, per favore riprova!\n");

        printf("Seleziona ruolo:\n1 - User\n2 - Admin\n");
        fflush(stdin);
        scanf("%d", &roleChoised);

        isRight = false;
    } while (roleChoised != 1 && roleChoised != 2);

    printf("Inserisci email\n");
    fflush(stdin);
    scanf("%s", (*user)->email);

    printf("Inserisci password\n");
    fflush(stdin);
    scanf("%s", (*user)->password);

    if (roleChoised == 1)
        foundIt = searchUser(userTree, &(*user)) == true;
    else
        foundIt = searchAdmin(userTree, &(*user)) == true;

    return foundIt;
}

bool search(UserTree userTree, User *user) {
    bool foundIt = false;

    if (strcmp(userTree->user->role, USER) == 0)
        foundIt = searchUser(userTree, &(*user));
    else
        foundIt = searchAdmin(userTree, &(*user));

    return foundIt;
}

bool searchUser(UserTree userTree, User *user) {
    bool isPresent = false;

    if (userTree != NULL) {
        if (strcmp(userTree->user->role, USER) == 0 && userEquals(userTree->user, *user)) {
            isPresent = true;
            copyUser(userTree->user, &(*user));
        }
        else
            isPresent = searchUser(userTree->sx, &(*user));
    }

    return isPresent;
}

bool searchAdmin(UserTree userTree, User *user) {
    bool isPresent = false;

    if (userTree != NULL) {
        if (strcmp(userTree->user->role, ADMIN) == 0 && userEquals(userTree->user, *user))
            isPresent = true;
        else
            isPresent = searchAdmin(userTree->dx, &(*user));
    }

    return isPresent;
}

bool userEquals(User u1, User u2) {
    return strcmp(u1->email, u2->email) == 0 && strcmp(u1->password, u2->password) == 0;
}

void inOrderUserTreePrint(UserTree T) {
    inOrderUserTree(T);
    printf("\n\n");
}

void preOrderUserTreePrint(UserTree T) {
    preOrderUserTree(T);
    printf("\n\n");
}

void postOrderUserTreePrint(UserTree T) {
    postOrderUserTree(T);
    printf("\n\n");
}

void inOrderUserTree(UserTree T) {
    if (T != NULL) {
        inOrderUserTree(T->sx);
        printUser(T->user);
        inOrderUserTree(T->dx);
    }
}

void preOrderUserTree(UserTree T) {
    if (T != NULL) {
        printUser(T->user);
        preOrderUserTree(T->sx);
        preOrderUserTree(T->dx);
    }
}

void postOrderUserTree(UserTree T) {
    if (T != NULL) {
        postOrderUserTree(T->sx);
        postOrderUserTree(T->dx);
        printUser(T->user);
    }
}

UserTree initUserNode(User user) {
    UserTree T = (UserTree) malloc(sizeof(struct TTreeUser));
    T->user = user;
    T->sx = NULL;
    T->dx = NULL;
    return T;
}

UserTree insertUserNodeTree(UserTree T, User user) {
    if (T == NULL) {
        T = initUserNode(user);
    } else {
        if (strcmp(user->role, USER) == 0) {
            T->sx = insertUserNodeTree(T->sx, user);
        } else {
            T->dx = insertUserNodeTree(T->dx, user);
        }
    }

    return T;
}

bool isEmptyUserTree(UserTree tree) {
    return tree == NULL;
}

void freeUserTree(UserTree T) {
    if (T) {
        freeUserTree(T->sx);
        freeUserTree(T->dx);
        free(T);
    }
}

void getAllUser(UserTree T) {
    if (T != NULL) {
        if (strcmp(T->user->role, USER) == 0)
            printUser(T->user);

        getAllUser(T->sx);
    }
}

void getAllUserPrint(UserTree T) {
    getAllUser(T);
    printf("\n\n");
}

void getAllAdmin(UserTree T) {
    if (T != NULL) {
        if (strcmp(T->user->role, ADMIN) == 0)
            printUser(T->user);

        getAllAdmin(T->dx);
    }
}

void getAllAdminPrint(UserTree T) {
    getAllAdmin(T);
    printf("\n\n");
}

int countUser(UserTree userTree) {
    int count = 0;

    while (userTree != NULL) {
        if (strcmp(userTree->user->role, USER) == 0) {
            count++;
        }

        userTree = userTree->sx;
    }

    return count;
}

int countAdmin(UserTree userTree) {
    int count = 0;

    while (userTree != NULL) {
        if (strcmp(userTree->user->role, ADMIN) == 0) {
            count++;
        }

        userTree = userTree->dx;
    }

    return count;
}

bool emailIsPresent(UserTree userTree, User user) {
    bool isPresent = false;

    if (userTree != NULL) {
        if (strcmp(user->role, ADMIN) == 0) {
            isPresent = emailAdminIsPresent(userTree, user->email);
        } else {
            isPresent = emailUserIsPresent(userTree, user->email);
        }
    }

    return isPresent;
}

bool emailUserIsPresent(UserTree userTree, char *email) {
    bool isPresent = false;

    if (userTree != NULL) {
        if (strcmp(userTree->user->role, USER) == 0 && strcmp(userTree->user->email, email) == 0)
            isPresent = true;
        else
            isPresent = emailUserIsPresent(userTree->sx, email);
    }

    return isPresent;
}

bool emailAdminIsPresent(UserTree userTree, char *email) {
    bool isPresent = false;

    if (userTree != NULL) {
        if (strcmp(userTree->user->role, ADMIN) == 0 && strcmp(userTree->user->email, email) == 0)
            isPresent = true;
        else
            isPresent = emailAdminIsPresent(userTree->dx, email);
    }

    return isPresent;
}

UserTree uploadAdmins(UserTree userTree) {
    char names[3][MAX_WORDS] = {"Luigi", "Piero Junior", "Giuliano"};
    char surnames[3][MAX_WORDS] = {"Audino", "Gaetani", "Galloppi"};
    char emails[3][MAX_WORDS] = {"luigi@mail.it", "piero@mail.it", "giuliano@mail.it"};

    for (int i = 0; i < 3; i++) {
        User user = (User) malloc(sizeof(struct usr));

        strcpy(user->role, ADMIN);
        strcpy(user->name, names[i]);
        strcpy(user->surname, surnames[i]);
        strcpy(user->email, emails[i]);
        strcpy(user->password, "admin");

        userTree = insertUserNodeTree(userTree, user);
    }

    return userTree;
}

void copyUser(User source, User *target) {
    if(source != NULL && target != NULL) {
        strcpy((*target)->name, source->name);
        strcpy((*target)->surname, source->surname);
        strcpy((*target)->role, source->role);
        strcpy((*target)->email, source->email);
        strcpy((*target)->password, source->password);
        (*target)->points = source->points;
    }
}
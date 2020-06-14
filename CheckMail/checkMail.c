#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "checkMail.h"

/*Gruppo 25 - Progetto 2 - Giuliano Galloppi N86001508; Piero Junior Gaetani N86002210; Luigi Audino N86001513*/




#ifdef DEBUG
#define DEBUG_MSG(var,val) printf("[DEBUG_MSG] %s = %d\n",var,val);
    #define PtrToChar(t,fun) \
            char t = *(data->str + data->pos);\
            data->pos++;\
            printf("%s -> \t\tt = %c\n",fun, t);
#else
#define DEBUG_MSG(var,val)
#define PtrToChar(t,fun) \
            char t = *(data->str + data->pos);\
            data->pos++;
#endif /* ifndef DEBUG */


#define MAX_STATES 10


typedef enum _states_t {
    st_init = 0,
    st_local_part= 1,
    st_local_part_dot= 2,
    st_domain_start = 3,
    st_domain_run = 4,
    st_domain_dot = 5,
    st_sub_domain = 6,
    st_allok = 7,
    st_error = 8,
}states_t ;


typedef struct checkMail {
    states_t state;
    char *str;
    unsigned long pos;
    unsigned long length;

    unsigned long domain_chars;  // Is reseted to length each time a non asic char is found

}checkMail /* optional variable list */;

//Prototipi di funzioni per la verifica della email digitata in input dall'utente.
void em_init(checkMail *data);
void em_local_part_start(checkMail *data);
void em_local_part_dot(checkMail *data);
void em_domain_start(checkMail *data);
void em_domain_run(checkMail *data);
void em_domain_dot(checkMail *data);

//Inizio codice di verifica email

int isEmail(char *str)
{
    /* typedef for function pointers */
    typedef void (*fptr)(checkMail *data );
    /* Init the struct with initial data */
    checkMail data = {
            .state = st_init,
            .str = str,
            .pos = 0,
            .length = strlen(str),
            .domain_chars = strlen(str),
            /* .local_part_ok = 0, */
            /* .domain_ok = 0, */
    };
#ifdef DEBUG
    printf("data.str = %s length = %li\n",data.str, data.length);
#endif


    fptr stateMachine[MAX_STATES];

    stateMachine[st_init] =             em_init;
    stateMachine[st_local_part] =       em_local_part_start;
    stateMachine[st_local_part_dot] =   em_local_part_dot;
    stateMachine[st_domain_start] =     em_domain_start;
    stateMachine[st_domain_run] =       em_domain_run;
    stateMachine[st_domain_dot] =       em_domain_dot;



    while (data.state != st_allok) {
        stateMachine[data.state](&data);
        if (data.state == st_error)
        {
#ifdef DEBUG
            printf("There was an ERROR %d\n", data.state);
#endif
            return 0;
        }

    }
    return 1;
}


void em_init(checkMail *data)
{
    PtrToChar(t,"em_init")


    if ((data->state == st_init) && (isalpha(t) != 0))
    {

        data->state=st_local_part;
    }
    else
    {
        data->state = st_error;
    }
}

void em_local_part_dot(checkMail *data)
{
    PtrToChar(t,"em_local_part_start")
    if (t == '.') {
        data->state = st_error;
    }
    else
    {
        data->state = st_local_part;
    }
}

void em_local_part_start(checkMail *data)
{
    PtrToChar(t,"em_local_part_start")
    if (data->pos < data->length) {

        if (((int)isalpha(t)||(int)isdigit(t)) == 0){
            switch (t) {
                case '@':
                    data->state = st_domain_start;
                    break;
                case '.':
                    data->state = st_local_part_dot;
                    break;
                case '_':
                    data->state = st_local_part;
                    break;
                default:
                    data->state = st_error;
            }
        }
    }
    else
    {

        data->state = st_error;
    }
}



void em_domain_start(checkMail *data)
{
    PtrToChar(t,"em_domain_start");
    data->state = st_error;
    /* The domain cant start with an special character
     * and the string can't be empty.
     */
    if ((data->pos <= data->length)&&((isalpha(t)||isdigit(t)) == 0)){
        DEBUG_MSG("Found non valid data",data->state)
        data->state = st_error;
    }
    else if (data->pos <= data->length)
    {
        DEBUG_MSG("Valid data",data->state)
        data->state = st_domain_run;
    }


}

void em_domain_run(checkMail *data)
{
    PtrToChar(t,"em_domain_run")
    data->state = st_error;
    if ((data->pos <= data->length)&&((isalpha(t)||isdigit(t)) == 0)){
        DEBUG_MSG("Found non valid data",data->state)
        switch (t) {
            case '.':
                DEBUG_MSG("case . state",data->state)
                data->state = st_domain_dot;
                data->domain_chars = data->pos - 1;
                /* data->domain_chars = 0; */
                break;
            case '-':
            case '_':
                DEBUG_MSG("case [-_] state",data->state)
                /* We cant have .c-c addresss */
                data->domain_chars = data->length;
                break;
            default:
                DEBUG_MSG("Default state",data->state)
                data->state = st_error;

        }

    }
    else if (data->pos <= data->length)
    {
        data->state = st_domain_run;
    }
    DEBUG_MSG("END em_domain_run ",data->state)
}

void em_domain_dot(checkMail *data)
{
    PtrToChar(t, "em_domain_dot")
    DEBUG_MSG("data->domain_chars=",(int)data->domain_chars)
    unsigned long int len = data->pos - data->domain_chars - 1;
#ifdef DEBUG
    int test = (2 <= len)&&( len <= 4);
#endif
    DEBUG_MSG("Len ",(int)len)
    DEBUG_MSG("is the subdomain between 2 and 4 characters ",test)
    if (4 < len) {
        data->state = st_domain_run;
    }
    else if ((isalpha(t) == 0)&&(isdigit(t) == 0))
    {
        DEBUG_MSG("Un known caracter",data->state)
        switch (t) {
            case '.':
                DEBUG_MSG("Found a dot '.' ", 0)
                data->domain_chars = data->pos - 1;
                data->state = st_domain_run;
                break;
            case '@':
            case '-':
            case '_':
                data->domain_chars = data->length;
                DEBUG_MSG("case [-_] state",data->state)
                break;
            default:
                data->state = st_error;
                DEBUG_MSG("default state",data->state)
        }

    }
    else if (data->pos == data->length)
    {
        DEBUG_MSG("Setting all st_allok ", 1)
        data->state = st_allok;
    }
}

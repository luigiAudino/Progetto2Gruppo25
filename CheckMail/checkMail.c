#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "checkMail.h"

/* Remove this line if you want to deactivate the debug output */
/* #define DEBUG */

/* Macros for defining messages and other practical abbriviations */
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
    /* int local_part_ok; */
    /* int domain_ok; */
    unsigned long domain_chars;  // Is reseted to length each time a non asic char is found
    /* int sub_domain_ok; */
    /* int sub_domain_counter; */
}checkMail /* optional variable list */;

//Prototipi di funzioni per la verifica della email digitata in input dall'utente.
void em_init(checkMail *data);
void em_local_part_start(checkMail *data);
void em_local_part_dot(checkMail *data);
void em_domain_start(checkMail *data);
void em_domain_run(checkMail *data);
void em_domain_dot(checkMail *data);

//Inizio codice di verifica email

/*! \brief This is the entry point to the
 * email validator library.
 *
 *  Detailed description.
 *  creates a function pointer array and inits
 *  the checkMail struct.
 *  Thin the it add the functions to the previously
 *  discussed function pointers.
 *
 *
 * \param *str is the input string contain a email
 * \return 1 if the string is a email else 0
 */
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

    /* Create an function pointer array. */
    fptr stateMachine[MAX_STATES];
    /* Populate the array with states */
    stateMachine[st_init] =             em_init;
    stateMachine[st_local_part] =       em_local_part_start;
    stateMachine[st_local_part_dot] =   em_local_part_dot;
    stateMachine[st_domain_start] =     em_domain_start;
    stateMachine[st_domain_run] =       em_domain_run;
    stateMachine[st_domain_dot] =       em_domain_dot;


    /* Start the state machine and continue
     * until st_error or st_allok.
     */
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

    /* This state is only viable when st_init and the first character is a alphanumeric character */
    if ((data->state == st_init) && (isalpha(t) != 0))
    {
        /* The first character was alphanumeric and the state is st_init */
        data->state=st_local_part;
    }
    else
    {
        data->state = st_error;
    }
}

/*! \brief If the next char is a "." then error
 *
 *  Detailed description of the function
 *
 * \param emailValidator_t *data The input to the state
 */
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

/*! \brief Enters the local part of the email
 *
 * The local part of an email is the part before the '@'
 * sign. This part can not have dual dots '..' thus the
 * local part is divided up in two parts.
 *
 * \param emailValidator_t *data The input to the state
 */
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
        /* You should never reach this position if it is a valid email adders.*/
        data->state = st_error;
    }
}



/*! \brief Enters the domain part of the email
 *
 *  The start of the domain name can not be a special
 *  character thus the start state checks if so sets
 *  the next state to st_error
 *
 * \param emailValidator_t *data The input to the state
 */
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

/*! \brief Continues run of the domain part.
 *
 *  If the start did not have any problem
 *  this part continues until it hits a
 *  dot '.' or the end.
 *
 * \param *data The input to the state
 */
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

/*! \brief If the domain contains a non alpha
 *
 *  If the domain contains a dot '.' then its
 *  ether the subdomain i.e .com or its a
 *  sub company domain like
 *
 *  @altern.engineering.se
 *
 *  In each case the rules are different.
 *  I.e the [.com,.se,.net,.eu] sub domains can
 *  only be 4 digits long and not contain
 *  any special case.
 *  While the .engeneering can contain
 *  dots and underscore signs and be longer then
 *  for characters.
 *
 *
 * \param *data The input to the state
 * \return none
 */
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

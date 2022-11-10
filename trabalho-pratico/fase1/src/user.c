#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"

USER *create_user(char *line)
{
    USER *u = malloc(sizeof(USER));

    u->username = strdup(strsep(&line, ";"));
    u->name = strdup(strsep(&line, ";"));
    u->gender = *((char *)strdup(strsep(&line, ";"))); // devolve o primeiro caracter da string
    u->date = strdup(strsep(&line, ";"));
    u->account_creation = strdup(strsep(&line, ";"));
    u->pay_method = strdup(strsep(&line, ";"));
    u->account_status = strdup(strsep(&line, "\n")); // o último caracter da linha é um '\n' e não um ';'

    return u;
}

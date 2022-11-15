#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"

USER *create_user(char *line)
{
    USER *u = malloc(sizeof(USER));

    u->username = strdup(strsep(&line, ";"));
    u->name = strdup(strsep(&line, ";"));
    u->gender = strdup(strsep(&line, ";"));
    u->birth_date = strdup(strsep(&line, ";"));
    u->account_creation = strdup(strsep(&line, ";"));
    u->pay_method = strdup(strsep(&line, ";"));
    u->account_status = strdup(strsep(&line, "\n")); // o último caracter da linha é um '\n' e não um ';'

    return u;
}

void destroy_user(void *v)
{
    USER *u = v;

    free(u->username);
    free(u->name);
    free(u->gender);
    free(u->birth_date);
    free(u->account_creation);
    free(u->pay_method);
    free(u->account_status);
    free(u);
}

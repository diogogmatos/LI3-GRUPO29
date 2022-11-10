#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/driver.h"

DRIVER *create_driver(char *line)
{
    DRIVER *d = malloc(sizeof(DRIVER));

    d->id = strdup(strsep(&line, ";"));
    d->name = strdup(strsep(&line, ";"));
    d->birth_day = strdup(strsep(&line, ";"));
    d->gender = *((char *)strdup(strsep(&line, ";"))); // devolve o primeiro caracter da string
    d->car_class = strdup(strsep(&line, ";"));
    d->license_plate = strdup(strsep(&line, ";"));
    d->city = strdup(strsep(&line, ";"));
    d->account_creation = strdup(strsep(&line, ";"));
    d->account_status = strdup(strsep(&line, "\n")); // o último caracter da linha é um '\n' e não um ';'

    return d;
}

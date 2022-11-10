#include "../include/driver.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODAY "09/10/2022"

double get_price(DRIVER *d)
{
    double r;

    switch (d->car_class[0])
    {
    case 'b':
        r = 3.25;
        return r;

    case 'g':
        r = 4.00;
        return r;

    case 'p':
        r = 5.20;
        return r;
    default:
        return 0;
    }
}

double get_tax(DRIVER *d)
{
    double r;

    switch (d->car_class[0])
    {
    case 'b':
        r = 0.62;
        return r;

    case 'g':
        r = 0.79;
        return r;

    case 'p':
        r = 0.94;
        return r;
    default:
        return 0;
    }
}

int convert_date(char *date)
{
    char *d = strdup(date);

    int dia = atoi(strsep(&d, "/"));
    int mes = atoi(strsep(&d, "/"));
    int ano = atoi(strsep(&d, "\0"));
    int r = ano * 365 + mes * 31 + dia;

    return r;
}

int get_age(char *date)
{
    int t = convert_date(TODAY);
    int d = convert_date(date);

    int r = (t - d) / 365;

    return r;
}

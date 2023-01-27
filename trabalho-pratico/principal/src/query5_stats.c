#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/ride.h"
#include "../include/utils.h"
#include "../include/catalog.h"
#include "../include/query5_stats.h"

struct stat
{
    char *date;
    double money;
    int trips;
};

// FUNÇÕES DESTROY

void destroy_bydate_stat(void *v)
{
    BYDATE_STAT *s = v;

    free(s->date);
    free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_bydate_stat(RIDE *r, GHashTable *bydate_stats, GHashTable *drivers)
{
    char *id = get_ride_driver(r);
    int id_int = atoi(id);
    DRIVER *d = g_hash_table_lookup(drivers, &id_int);

    char *date = get_ride_date(r);

    BYDATE_STAT *sl = g_hash_table_lookup(bydate_stats, date);

    int distance = get_ride_distance(r);

    if (sl == NULL)
    {
        BYDATE_STAT *s = malloc(sizeof(BYDATE_STAT));

        s->date = date;
        s->money = get_price(d) + get_tax(d) * distance;
        s->trips = 1;

        g_hash_table_insert(bydate_stats, s->date, s);
    }
    else
    {
        sl->money += get_price(d) + get_tax(d) * distance;
        sl->trips++;

        free(date);
    }

    free(id);
}

double create_query5_stat(char *date_a, char *date_b, CATALOG *c)
{
    double m = 0, t = 0, r = 0;

    increase_date(date_b);

    char *date;
    for (date = date_a; strcmp(date, date_b); increase_date(date))
    {
        BYDATE_STAT *s = g_hash_table_lookup(get_catalog_bydate_stats(c), date);

        if (s != NULL)
        {
            m += s->money;
            t += s->trips;
        }
    }

    if (m == 0) // não temos de verificar se t == 0, pois se m == 0, então t == 0 (e vice-versa)
        r = -1;
    else
        r = m / t;

    return r;
}

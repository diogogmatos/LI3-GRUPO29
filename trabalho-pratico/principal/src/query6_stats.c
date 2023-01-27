#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/utils.h"
#include "../include/catalog.h"
#include "../include/query6_stats.h"

struct stat
{
    char *citydate;
    int distance;
    int trips;
};

// FUNÇÕES DESTROY

void destroy_bycitydate_stat(void *v)
{
    BYCITYDATE_STAT *s = v;

    free(s->citydate);
    free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_bycitydate_stat(RIDE *r, GHashTable *bycitydate_stats)
{
    char *city = get_ride_city(r);
    char *date = get_ride_date(r);

    char *citydate = malloc(strlen(city) + strlen(date) + 2);
    sprintf(citydate, "%s-%s", city, date);

    BYCITYDATE_STAT *sl = g_hash_table_lookup(bycitydate_stats, citydate);

    int distance = get_ride_distance(r);

    if (sl == NULL)
    {
        BYCITYDATE_STAT *s = malloc(sizeof(BYCITYDATE_STAT));

        s->citydate = citydate;
        s->distance = distance;
        s->trips = 1;

        g_hash_table_insert(bycitydate_stats, s->citydate, s);
    }
    else
    {
        sl->distance += distance;
        sl->trips++;

        free(citydate);
    }

    free(city);
    free(date);
}

double create_query6_stat(char *city, char *date_a, char *date_b, CATALOG *c)
{
    double d = 0, t = 0, r = 0;

    char *citydate_a = malloc(strlen(city) + strlen(date_a) + 2);
    sprintf(citydate_a, "%s-%s", city, date_a);

    char *citydate_b = malloc(strlen(city) + strlen(date_b) + 2);
    sprintf(citydate_b, "%s-%s", city, date_b);

    increase_something_date(citydate_b);

    char *citydate;
    for (citydate = citydate_a; strcmp(citydate, citydate_b); increase_something_date(citydate))
    {
        BYCITYDATE_STAT *s = g_hash_table_lookup(get_catalog_bycitydate_stats(c), citydate);

        if (s != NULL)
        {
            d += s->distance;
            t += s->trips;
        }
    }

    free(citydate_a);
    free(citydate_b);

    if (d == 0) // não temos de verificar se t == 0, pois se d == 0, então t == 0 (e vice-versa)
        r = -1;
    else
        r = d / t;

    return r;
}

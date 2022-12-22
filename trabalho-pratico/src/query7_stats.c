#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/ride.h"
#include "../include/catalog.h"
#include "../include/query7_stats.h"

struct stat
{
    char *city;
    CATALOG *c;
    GHashTable *ht;

    char *id;
    char *driver_name;
    int trips;
    double score;
    double avg_score;
};

// FUNÇÕES GET

char *get_query7_stat_id(QUERY7_STAT *s)
{
    return strdup(s->id);
}

char *get_query7_stat_driver_name(QUERY7_STAT *s)
{
    return strdup(s->driver_name);
}

double get_query7_stat_avg_score(QUERY7_STAT *s)
{
    return s->avg_score;
}

// FUNÇÕES DESTROY

void destroy_query7_stat(void *v)
{
    QUERY7_STAT *s = v;

    free(s->id);
    free(s->driver_name);
    free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void build_query7_stat(gpointer key, gpointer value, gpointer userdata)
{
    RIDE *r = value;
    QUERY7_STAT *s = userdata;

    char *id = get_ride_driver(r);
    DRIVER *d = g_hash_table_lookup(get_catalog_drivers(s->c), id);

    char *account_status = get_driver_account_status(d);

    if (!strcmp(account_status, "active")) // Apenas se a conta do condutor estiver ativa
    {
        char *city = get_ride_city(r);

        if (!strcmp(city, s->city)) // Apenas considerados os valores de viagens efetuadas na cidade pretendida
        {
            QUERY7_STAT *dl = g_hash_table_lookup(s->ht, id);

            if (dl == NULL) // Se o condutor ainda não está na tabela hash, inicializamos os dados e adicionamos à tabela
            {
                QUERY7_STAT *driver_stat = malloc(sizeof(QUERY7_STAT));
                DRIVER *d = g_hash_table_lookup(get_catalog_drivers(s->c), id);

                driver_stat->id = id;
                driver_stat->driver_name = get_driver_name(d);

                driver_stat->trips = 1;
                driver_stat->score = get_ride_score_driver(r);
                driver_stat->avg_score = driver_stat->score;

                g_hash_table_insert(s->ht, driver_stat->id, driver_stat);
            }
            else // Se o condutor já está na tabela hash, atualizamos os dados
            {
                dl->trips += 1;
                dl->score += get_ride_score_driver(r);
                dl->avg_score = dl->score / dl->trips;

                free(id);
            }
        }
        else
            free(id);

        free(city);
    }
    else
        free(id);

    free(account_status);
}

void create_query7_stats(GHashTable *query7_stats, char *city, CATALOG *c)
{
    QUERY7_STAT *s = malloc(sizeof(QUERY7_STAT)); // Usada para passar valores à função `create_query7_stat()`

    s->ht = query7_stats;
    s->city = city;
    s->c = c;

    g_hash_table_foreach(get_catalog_rides(c), build_query7_stat, s);

    free(s);
}

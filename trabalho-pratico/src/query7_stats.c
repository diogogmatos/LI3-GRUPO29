#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/ride.h"
#include "../include/driver.h"
#include "../include/query7_stats.h"

struct stat
{
    char *citydriver;
    double score;
    int trips;
    double avg_score;
};

// FUNÇÕES GET

char *get_query7_stat_citydriver(QUERY7_STAT *s)
{
    return strdup(s->citydriver);
}

double get_query7_stat_avg_score(QUERY7_STAT *s)
{
    return s->avg_score;
}

// FUNÇÕES DESTROY

void destroy_query7_stat(void *v)
{
    QUERY7_STAT *s = v;

    free(s->citydriver);
    free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_query7_stat(RIDE *r, GHashTable *query7_stats, GHashTable *drivers)
{
    char *id = get_ride_driver(r);
    int id_int = atoi(id);
    char *account_status = get_driver_account_status(g_hash_table_lookup(drivers, &id_int));

    if (!strcmp(account_status, "active"))
    {
        char *city = get_ride_city(r);

        char *citydriver = malloc(strlen(city) + strlen(id) + 2);
        sprintf(citydriver, "%s-%s", city, id);

        QUERY7_STAT *sl = g_hash_table_lookup(query7_stats, citydriver);

        double score = get_ride_score_driver(r);

        if (sl == NULL)
        {
            QUERY7_STAT *s = malloc(sizeof(QUERY7_STAT));

            s->citydriver = citydriver;
            s->score = score;
            s->trips = 1;
            s->avg_score = score;

            g_hash_table_insert(query7_stats, s->citydriver, s);
        }
        else
        {
            sl->score += score;
            sl->trips++;
            sl->avg_score = sl->score / sl->trips;

            free(citydriver);
        }

        free(city);
    }

    free(account_status);
    free(id);
}

gint compare_query7_stats(gconstpointer a, gconstpointer b)
{
    QUERY7_STAT *s1 = (QUERY7_STAT *)a;
    QUERY7_STAT *s2 = (QUERY7_STAT *)b;

    int r;

    double avg_score1 = s1->avg_score;
    double avg_score2 = s2->avg_score;

    if (avg_score1 > avg_score2)
        r = -1;
    else if (avg_score1 < avg_score2)
        r = 1;
    else
    {
        char *id1 = strchr(s1->citydriver, '-') + 1;
        char *id2 = strchr(s2->citydriver, '-') + 1;

        if (strcmp(id1, id2) > 0)
            r = -1;
        else
            r = 1;
    }

    return r;
}

GList *sort_query7_stats(GHashTable *query7_stats)
{
    GList *list = g_hash_table_get_values(query7_stats);

    list = g_list_sort(list, compare_query7_stats);

    return list;
}

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/stats.h"
#include "../include/driver_stats.h"
#include "../include/user_stats.h"
#include "../include/city_stats.h"
#include "../include/query5_stats.h"
#include "../include/query6_stats.h"
#include "../include/query7_stats.h"
#include "../include/query8_stats.h"

struct stats
{
    GHashTable *driver_stats;
    GList *query2_stats;
    GHashTable *user_stats;
    GList *query3_stats;
    GHashTable *city_stats;
    GHashTable *bydate_stats;
    GHashTable *bycitydate_stats;
    GHashTable *query7_stats_hash;
    GList *query7_stats;
    GHashTable *query8_stats_hash;
    GList *query8_stats;
};

// FUNÇÕES GET

GHashTable *get_driver_stats(STATS *s)
{
    return s->driver_stats;
}

GHashTable *get_user_stats(STATS *s)
{
    return s->user_stats;
}

GHashTable *get_city_stats(STATS *s)
{
    return s->city_stats;
}

GList *get_query2_stats(STATS *s)
{
    return s->query2_stats;
}

GList *get_query3_stats(STATS *s)
{
    return s->query3_stats;
}

GHashTable *get_bydate_stats(STATS *s)
{
    return s->bydate_stats;
}

GHashTable *get_bycitydate_stats(STATS *s)
{
    return s->bycitydate_stats;
}

GHashTable *get_query7_stats_hash(STATS *s)
{
    return s->query7_stats_hash;
}

GList *get_query7_stats(STATS *s)
{
    return s->query7_stats;
}

GHashTable *get_query8_stats_hash(STATS *s)
{
    return s->query8_stats_hash;
}

GList *get_query8_stats(STATS *s)
{
    return s->query8_stats;
}

// FUNÇÕES CREATE / DESTROY

STATS *create_stats()
{
    STATS *s = malloc(sizeof(STATS));

    GHashTable *driver_stats = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, destroy_driver_stat);         // estatísticas de condutores
    GHashTable *user_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_user_stat);             // estatísticas de utilizadores
    GHashTable *city_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_city_stat);             // estatísticas da query 4
    GHashTable *bydate_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_bydate_stat);         // estatísticas da query 5
    GHashTable *bycitydate_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_bycitydate_stat); // estatísticas da query 6
    GHashTable *query7_stats_hash = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_query7_stat);    // estatísticas da query 7 (hash table)
    GHashTable *query8_stats_hash = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, destroy_query8_stat);    // estatísticas da query 8 (hash table)

    s->driver_stats = driver_stats;
    s->user_stats = user_stats;
    s->city_stats = city_stats;
    s->bydate_stats = bydate_stats;
    s->bycitydate_stats = bycitydate_stats;
    s->query7_stats_hash = query7_stats_hash;
    s->query8_stats_hash = query8_stats_hash;

    return s;
}

void destroy_stats(void *v)
{
    STATS *s = v;

    g_list_free(s->query2_stats);
    g_hash_table_destroy(s->driver_stats);
    g_list_free(s->query3_stats);
    g_hash_table_destroy(s->user_stats);
    g_hash_table_destroy(s->city_stats);
    g_hash_table_destroy(s->bydate_stats);
    g_hash_table_destroy(s->bycitydate_stats);
    g_list_free(s->query7_stats);
    g_hash_table_destroy(s->query7_stats_hash);
    g_list_free(s->query8_stats);
    g_hash_table_destroy(s->query8_stats_hash);
    free(s);
}

// OUTROS

void sort_stats(STATS *s)
{
    GList *query2_stats = sort_query2_stats(s->driver_stats);      // estatísticas da query 2 (lista ordenada)
    GList *query3_stats = sort_query3_stats(s->user_stats);        // estatísticas da query 3 (lista ordenada)
    GList *query7_stats = sort_query7_stats(s->query7_stats_hash); // estatísticas da query 7 (lista ordenada)
    GList *query8_stats = sort_query8_stats(s->query8_stats_hash); // estatísticas da query 8 (lista ordenada)

    s->query2_stats = query2_stats;
    s->query3_stats = query3_stats;
    s->query7_stats = query7_stats;
    s->query8_stats = query8_stats;
}

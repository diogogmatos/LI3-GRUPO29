#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/catalog.h"
#include "../include/user_stats.h"
#include "../include/driver_stats.h"
#include "../include/city_stats.h"
#include "../include/query5_stats.h"
#include "../include/query6_stats.h"
#include "../include/query7_stats.h"
#include "../include/query8_stats.h"

/* Struct CATALOG
 * Responsável por guardar os apontadores para as 3 hash table de dados (drivers, users e rides),
 * de modo a facilitar o acesso a cada uma delas em diversos casos.
 */
struct catalog
{
    GHashTable *drivers;
    GHashTable *users;
    GHashTable *rides;

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

GHashTable *get_catalog_drivers(CATALOG *c)
{
    return c->drivers;
}

GHashTable *get_catalog_users(CATALOG *c)
{
    return c->users;
}

GHashTable *get_catalog_rides(CATALOG *c)
{
    return c->rides;
}

GHashTable *get_catalog_driver_stats(CATALOG *c)
{
    return c->driver_stats;
}

GHashTable *get_catalog_user_stats(CATALOG *c)
{
    return c->user_stats;
}

GHashTable *get_catalog_city_stats(CATALOG *c)
{
    return c->city_stats;
}

GList *get_catalog_query2_stats(CATALOG *c)
{
    return c->query2_stats;
}

GList *get_catalog_query3_stats(CATALOG *c)
{
    return c->query3_stats;
}

GHashTable *get_catalog_bydate_stats(CATALOG *c)
{
    return c->bydate_stats;
}

GHashTable *get_catalog_bycitydate_stats(CATALOG *c)
{
    return c->bycitydate_stats;
}

GList *get_catalog_query7_stats(CATALOG *c)
{
    return c->query7_stats;
}

GList *get_catalog_query8_stats(CATALOG *c)
{
    return c->query8_stats;
}

// FUNÇÕES CREATE / DESTROY

/* Função `create_catalog()`
 * Responsável por inicializar a struct CATALOG com os 3 módulos de dados (drivers, users e rides),
 * chamando as funções read_<módulo>() que fazem o parsing dos dados dos drivers, users e rides, respetivamente.
 */
CATALOG *create_catalog(char *dataset)
{
    CATALOG *c = malloc(sizeof(CATALOG));

    GHashTable *drivers = read_drivers(dataset); // dados de condutores
    GHashTable *users = read_users(dataset);     // dados de utilizadores

    GHashTable *driver_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_driver_stat);         // estatísticas de condutores
    GHashTable *user_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_user_stat);             // estatísticas de utilizadores
    GHashTable *city_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_city_stat);             // estatísticas da query 4
    GHashTable *bydate_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_bydate_stat);         // estatísticas da query 5
    GHashTable *bycitydate_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_bycitydate_stat); // estatísticas da query 6
    GHashTable *query7_stats_hash = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_query7_stat);    // estatísticas da query 7 (hash table)
    GHashTable *query8_stats_hash = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, destroy_query8_stat);    // estatísticas da query 8 (hash table)

    GHashTable *rides = read_rides(dataset, user_stats, driver_stats, city_stats, bydate_stats, bycitydate_stats, query7_stats_hash, query8_stats_hash, drivers, users); // dados de viagens

    GList *query2_stats = sort_query2_stats(driver_stats);      // estatísticas da query 2 (lista ordenada)
    GList *query3_stats = sort_query3_stats(user_stats);        // estatísticas da query 3 (lista ordenada)
    GList *query7_stats = sort_query7_stats(query7_stats_hash); // estatísticas da query 7 (lista ordenada)
    GList *query8_stats = sort_query8_stats(query8_stats_hash); // estatísticas da query 8 (lista ordenada)

    c->drivers = drivers;
    c->users = users;
    c->rides = rides;

    c->driver_stats = driver_stats;
    c->user_stats = user_stats;
    c->city_stats = city_stats;
    c->query2_stats = query2_stats;
    c->query3_stats = query3_stats;
    c->bydate_stats = bydate_stats;
    c->bycitydate_stats = bycitydate_stats;
    c->query7_stats_hash = query7_stats_hash;
    c->query7_stats = query7_stats;
    c->query8_stats_hash = query8_stats_hash;
    c->query8_stats = query8_stats;

    return c;
}

void destroy_catalog(void *v)
{
    CATALOG *c = v;

    g_hash_table_destroy(c->drivers);
    g_hash_table_destroy(c->users);
    g_hash_table_destroy(c->rides);
    g_list_free(c->query2_stats);
    g_hash_table_destroy(c->driver_stats);
    g_list_free(c->query3_stats);
    g_hash_table_destroy(c->user_stats);
    g_hash_table_destroy(c->city_stats);
    g_hash_table_destroy(c->bydate_stats);
    g_hash_table_destroy(c->bycitydate_stats);
    g_list_free(c->query7_stats);
    g_hash_table_destroy(c->query7_stats_hash);
    g_list_free(c->query8_stats);
    g_hash_table_destroy(c->query8_stats_hash);
    free(c);
}

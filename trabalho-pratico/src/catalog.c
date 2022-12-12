#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/catalog.h"
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/stat.h"

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
    GHashTable *user_stats;
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

// FUNÇÕES CREATE / DESTROY

/* Função `create_catalog()`
 * Responsável por inicializar a struct CATALOG com os 3 módulos de dados (drivers, users e rides),
 * chamando as funções read_<módulo>() que fazem o parsing dos dados dos drivers, users e rides, respetivamente.
 */
CATALOG *create_catalog(char *dataset)
{
    CATALOG *c = malloc(sizeof(CATALOG));

    GHashTable *drivers = read_drivers(dataset);
    GHashTable *users = read_users(dataset);
    
    GHashTable *driver_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_driver_stat);
    GHashTable *user_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_user_stat);
    GHashTable *rides = read_rides(dataset, user_stats, driver_stats, drivers, users);

    c->drivers = drivers;
    c->users = users;
    c->rides = rides;

    c->driver_stats = driver_stats;
    c->user_stats = user_stats;

    return c;
}

void destroy_catalog(void *v)
{
    CATALOG *c = v;

    g_hash_table_destroy(c->drivers);
    g_hash_table_destroy(c->users);
    g_hash_table_destroy(c->rides);
    g_hash_table_destroy(c->driver_stats);
    g_hash_table_destroy(c->user_stats);
    free(c);
}

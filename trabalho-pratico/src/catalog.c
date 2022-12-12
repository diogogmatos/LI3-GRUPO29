#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/catalog.h"
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"

/* Struct CATALOG
 * Responsável por guardar os apontadores para as 3 hash table de dados (drivers, users e rides),
 * de modo a facilitar o acesso a cada uma delas em diversos casos.
 */
struct catalog
{
    GHashTable *drivers;
    GHashTable *users;
    GHashTable *rides;
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
    GHashTable *rides = read_rides(dataset);

    c->drivers = drivers;
    c->users = users;
    c->rides = rides;

    return c;
}

void destroy_catalog(void *v)
{
    CATALOG *c = v;

    g_hash_table_destroy(c->drivers);
    g_hash_table_destroy(c->users);
    g_hash_table_destroy(c->rides);
    free(c);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/catalog.h"
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"

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

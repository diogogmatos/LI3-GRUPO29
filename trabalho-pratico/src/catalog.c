#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/catalog.h"
#include "../include/parsing.h"

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

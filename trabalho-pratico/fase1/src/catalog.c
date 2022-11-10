#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/catalog.h"
#include "../include/parsing.h"

CATALOG *create_catalog()
{
    CATALOG *c = malloc(sizeof(CATALOG));

    GHashTable *drivers = read_drivers();
    GHashTable *users = read_users();
    GHashTable *rides = read_rides();

    c->drivers = drivers;
    c->users = users;
    c->rides = rides;

    return c;
}

#ifndef catalog_h
#define catalog_h

#include <glib.h>

typedef struct catalog CATALOG;

// FUNÇÕES GET

GHashTable *get_catalog_drivers(CATALOG *c);
GHashTable *get_catalog_users(CATALOG *c);
GHashTable *get_catalog_rides(CATALOG *c);

// FUNÇÕES CREATE / DESTROY

CATALOG *create_catalog(char *dataset);
void destroy_catalog(void *v);

#endif
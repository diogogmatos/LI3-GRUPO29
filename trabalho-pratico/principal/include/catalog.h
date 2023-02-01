#ifndef catalog_h
#define catalog_h

#include <glib.h>

typedef struct catalog CATALOG;

// FUNÇÕES GET

GHashTable *get_catalog_drivers(CATALOG *c);
GHashTable *get_catalog_users(CATALOG *c);
GHashTable *get_catalog_rides(CATALOG *c);

GHashTable *get_catalog_driver_stats(CATALOG *c);
GHashTable *get_catalog_user_stats(CATALOG *c);
GHashTable *get_catalog_city_stats(CATALOG *c);
GList *get_catalog_query2_stats(CATALOG *c);
GList *get_catalog_query3_stats(CATALOG *c);
GHashTable *get_catalog_bydate_stats(CATALOG *c);
GHashTable *get_catalog_bycitydate_stats(CATALOG *c);
GList *get_catalog_query7_stats(CATALOG *c);
GList *get_catalog_query8_stats(CATALOG *c);

// FUNÇÕES CREATE / DESTROY

CATALOG *create_catalog(char *dataset, int v);
void destroy_catalog(void *v);

#endif
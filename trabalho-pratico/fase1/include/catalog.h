#ifndef catalog_h
#define catalog_h

#include <glib.h>

typedef struct catalog
{
    GHashTable *drivers;
    GHashTable *users;
    GHashTable *rides;
} CATALOG;

CATALOG *create_catalog();

#endif
#ifndef catalog_h
#define catalog_h

#include <glib.h>

/* Struct CATALOG
 * Responsável por guardar os apontadores para as 3 hash table de dados (drivers, users e rides),
 * de modo a facilitar o acesso a cada uma delas em diversos casos.
 */
typedef struct catalog
{
    GHashTable *drivers;
    GHashTable *users;
    GHashTable *rides;
} CATALOG;

CATALOG *create_catalog(char *dataset);

#endif
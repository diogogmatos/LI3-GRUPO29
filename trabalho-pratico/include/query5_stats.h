#ifndef query5_stats_h
#define query5_stats_h

#include <glib.h>
#include "ride.h"
#include "catalog.h"

typedef struct stat BYDATE_STAT;

void destroy_bydate_stat(void *v);

void create_bydate_stat(RIDE *r, GHashTable *bydate_stats, GHashTable *drivers);
double create_query5_stat(char *date_a, char *date_b, CATALOG *c);

#endif
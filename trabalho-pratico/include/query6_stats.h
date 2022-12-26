#ifndef query6_stats_h
#define query6_stats_h

#include <glib.h>
#include "catalog.h"

typedef struct stat QUERY6_STAT;

double create_query6_stat(char *city, char *date_a, char *date_b, CATALOG *c);

#endif
#ifndef query5_stats_h
#define query5_stats_h

#include <glib.h>
#include "catalog.h"

typedef struct stat QUERY5_STAT;

double create_query5_stat(char *date_a, char *date_b, CATALOG *c);

#endif
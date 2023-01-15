#ifndef query7_stats_h
#define query7_stats_h

#include <glib.h>
#include "../include/ride.h"

typedef struct stat QUERY7_STAT;

char *get_query7_stat_citydriver(QUERY7_STAT *s);
double get_query7_stat_avg_score(QUERY7_STAT *s);

void destroy_query7_stat(void *v);

void create_query7_stat(RIDE *r, GHashTable *query7_stats, GHashTable *drivers);
GList *sort_query7_stats(GHashTable *query7_stats);

#endif
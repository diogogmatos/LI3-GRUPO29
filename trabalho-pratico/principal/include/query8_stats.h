#ifndef query8_stats_h
#define query8_stats_h

#include <glib.h>
#include "stats.h"

typedef struct stat QUERY8_STAT;

char *get_query8_stat_gender(QUERY8_STAT *s);
int get_query8_stat_ride(QUERY8_STAT *s);
double get_query8_stat_driver_acc_age(QUERY8_STAT *s);
double get_query8_stat_user_acc_age(QUERY8_STAT *s);

void destroy_query8_stat(void *v);

void create_query8_stats(RIDE *r, GHashTable *query8_stats, GHashTable *drivers, GHashTable *users);
GList *sort_query8_stats(GHashTable *query8_stats);

#endif
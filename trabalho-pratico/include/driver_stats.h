#ifndef driver_stats_h
#define driver_stats_h

#include <glib.h>
#include "ride.h"

typedef struct stat DRIVER_STAT;

// FUNÇÕES GET

char *get_driver_stat_id(DRIVER_STAT *s);
char *get_driver_stat_driver_name(DRIVER_STAT *s);
char *get_driver_stat_gender(DRIVER_STAT *s);
int get_driver_stat_age(DRIVER_STAT *s);
char *get_driver_stat_city(DRIVER_STAT *s);
double get_driver_stat_score(DRIVER_STAT *s);
double get_driver_stat_avg_score(DRIVER_STAT *s);
int get_driver_stat_trips(DRIVER_STAT *s);
double get_driver_stat_money(DRIVER_STAT *s);
int get_driver_stat_total_distance(DRIVER_STAT *s);
char *get_driver_stat_most_recent_trip(DRIVER_STAT *s);

// FUNÇÕES DESTROY

void destroy_driver_stat(void *v);

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_driver_stat(RIDE *r, GHashTable *d_stats, GHashTable *drivers);
GList *sort_query2_stats(GHashTable *driver_stats);

#endif
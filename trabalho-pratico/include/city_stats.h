#ifndef city_stats_h
#define city_stats_h

#include <glib.h>
#include "ride.h"

typedef struct stat CITY_STAT;

// FUNÇÕES GET

char *get_city_stat_city(CITY_STAT *s);
int get_city_stat_trips(CITY_STAT *s);
double get_city_stat_money(CITY_STAT *s);
double get_city_stat_avg_cost(CITY_STAT *s);

// FUNÇÕES DESTROY

void destroy_city_stat(void *v);

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_city_stat(RIDE *r, GHashTable *c_stats, GHashTable *drivers);

#endif
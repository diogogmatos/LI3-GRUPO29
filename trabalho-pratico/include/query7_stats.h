#ifndef query7_stats_h
#define query7_stats_h

#include <glib.h>
#include "catalog.h"

typedef struct stat QUERY7_STAT;

// FUNÇÕES GET

char *get_query7_stat_id(QUERY7_STAT *s);
char *get_query7_stat_driver_name(QUERY7_STAT *s);
double get_query7_stat_avg_score(QUERY7_STAT *s);

// FUNÇÕES DESTROY

void destroy_query7_stat(void *v);

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_query7_stats(GHashTable *query7_stats, char *city, CATALOG *c);

#endif
#ifndef query9_stats_h
#define query9_stats_h

#include <glib.h>
#include "catalog.h"

typedef struct stat QUERY9_STAT;

// FUNÇÕES GET

char *get_query9_stat_id(QUERY9_STAT *s);
char *get_query9_stat_date(QUERY9_STAT *s);
char *get_query9_stat_city(QUERY9_STAT *s);
int get_query9_distance(QUERY9_STAT *s);
double get_query9_tip(QUERY9_STAT *s);

// FUNÇÕES DESTROY

void destroy_query9_stat(void *v);

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_query9_stats(GHashTable *query9_stats, char *date_a, char *date_b, CATALOG *c);

#endif
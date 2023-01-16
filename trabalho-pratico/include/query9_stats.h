#ifndef query9_stats_h
#define query9_stats_h

#include <glib.h>
#include "catalog.h"

typedef struct stat QUERY9_STAT;
typedef struct aux QUERY9_AUX;

// FUNÇÕES GET

char *get_query9_stat_id(QUERY9_STAT *s);
int get_query9_stat_id_int(QUERY9_STAT *s);
char *get_query9_stat_date(QUERY9_STAT *s);
char *get_query9_stat_city(QUERY9_STAT *s);
int get_query9_stat_distance(QUERY9_STAT *s);
double get_query9_stat_tip(QUERY9_STAT *s);

// FUNÇÕES DESTROY

void destroy_query9_stat(void *v);

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

GSList *create_query9_stats(char *date_a, char *date_b, CATALOG *c);

#endif
#ifndef query6_stats_h
#define query6_stats_h

#include <glib.h>
#include "ride.h"
#include "stats.h"

typedef struct stat BYCITYDATE_STAT;

// FUNÇÕES DESTROY

void destroy_bycitydate_stat(void *v);

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_bycitydate_stat(RIDE *r, GHashTable *bycitydate_stats);
double create_query6_stat(char *city, char *date_a, char *date_b, STATS *s);

#endif
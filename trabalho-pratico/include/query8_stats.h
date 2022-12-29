#ifndef query8_stats_h
#define query8_stats_h

#include <glib.h>
#include "catalog.h"

typedef struct stat QUERY8_STAT;
typedef struct aux QUERY8_AUX;

// FUNÇÕES GET

char *get_query8_stat_ride_id(QUERY8_STAT *s);
char *get_query8_stat_id(QUERY8_STAT *s);
char *get_query8_stat_username(QUERY8_STAT *s);
int get_query8_stat_acc_age_d(QUERY8_STAT *s);
int get_query8_stat_acc_age_u(QUERY8_STAT *s);

// FUNÇÕES DESTROY

void destroy_query8_stat(void *v);

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

GSList *create_query8_stats(char *gender, int X, CATALOG *c);

#endif
#ifndef user_stats_h
#define user_stats_h

#include <glib.h>
#include "ride.h"

typedef struct stat USER_STAT;

// FUNÇÕES GET

char *get_user_stat_username(USER_STAT *s);
char *get_user_stat_user_name(USER_STAT *s);
char *get_user_stat_gender(USER_STAT *s);
int get_user_stat_age(USER_STAT *s);
double get_user_stat_score(USER_STAT *s);
double get_user_stat_avg_score(USER_STAT *s);
int get_user_stat_trips(USER_STAT *s);
double get_user_stat_money(USER_STAT *s);
int get_user_stat_total_distance(USER_STAT *s);
char *get_user_stat_most_recent_trip(USER_STAT *s);

// FUNÇÕES DESTROY

void destroy_user_stat(void *v);

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_user_stat(RIDE *r, GHashTable *u_stats, GHashTable *drivers, GHashTable *users);
GList *sort_query3_stats(GHashTable *user_stats);

#endif
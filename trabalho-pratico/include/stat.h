#ifndef stat_h
#define stat_h

#include "../include/user.h"
#include "../include/driver.h"
#include "../include/catalog.h"
#include <glib.h>

typedef struct stat STAT;

// FUNÇÕES GET

int get_stat_age(STAT *s);
double get_stat_money(STAT *s);
double get_stat_score(STAT *s);
char *get_stat_driver_name(STAT *s);
char *get_stat_user_name(STAT *s);
int get_stat_total_distance(STAT *s);
char *get_stat_id(STAT *s);
double get_stat_avg_score(STAT *s);
int get_stat_trips(STAT *s);
char *get_stat_username(STAT *s);
char *get_stat_most_recent_trip(STAT *s);

// FUNÇÕES DESTROY

void destroy_stat_avg_score(void *v);
void destroy_stat_tot_dist(void *v);

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

STAT *user_stat(USER *u, CATALOG *c);
STAT *driver_stat(DRIVER *d, CATALOG *c);
void avg_score_stats(GHashTable *ht, CATALOG *c);
void tot_dist_stats(GHashTable *ht, CATALOG *c);

#endif

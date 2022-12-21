#ifndef stat_h
#define stat_h

#include "../include/user.h"
#include "../include/driver.h"
#include "../include/ride.h"
#include "../include/catalog.h"
#include <glib.h>

typedef struct stat STAT;

// FUNÇÕES GET

int get_stat_age(STAT *s);
double get_stat_money(STAT *s);
char *get_stat_gender(STAT *s);
double get_stat_score(STAT *s);
char *get_stat_driver_name(STAT *s);
char *get_stat_user_name(STAT *s);
int get_stat_total_distance(STAT *s);
char *get_stat_city(STAT *s);
double get_stat_avg_cost(STAT *s);
char *get_stat_id(STAT *s);
double get_stat_avg_score(STAT *s);
int get_stat_trips(STAT *s);
int get_stat_acc_age_d(STAT *s);
int get_stat_acc_age_u(STAT *s);
char *get_stat_ride_id(STAT *s);
char *get_stat_username(STAT *s);
char *get_stat_most_recent_trip(STAT *s);

// FUNÇÕES DESTROY

void destroy_user_stat(void *v);
void destroy_driver_stat(void *v);
void destroy_city_stat(void *v);
void destroy_query7_stat(void *v);
void destroy_query8_stat(void *v);

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_user_stat(RIDE *r, GHashTable *u_stats, GHashTable *drivers, GHashTable *users);
void create_driver_stat(RIDE *r, GHashTable *d_stats, GHashTable *drivers);
void create_city_stat(RIDE *r, GHashTable *c_stats, GHashTable *drivers);
double create_query5_stat(char *date_a, char *date_b, CATALOG *c);
void create_query7_stats(GHashTable *query7_stats, char *city, CATALOG *c);
void create_query8_stats(GHashTable *query8_stats, char *gender, int X, CATALOG *c);

#endif

#ifndef ride_h
#define ride_h

#include <glib.h>

typedef struct ride RIDE;

// FUNÇÕES GET

char *get_ride_id(RIDE *r);
char *get_ride_date(RIDE *r);
char *get_ride_driver(RIDE *r);
char *get_ride_user(RIDE *r);
char *get_ride_city(RIDE *r);
int get_ride_distance(RIDE *r);
int get_ride_score_user(RIDE *r);
int get_ride_score_driver(RIDE *r);
double get_ride_tip(RIDE *r);
char *get_ride_comment(RIDE *r);

// FUNÇÕES CREATE / DESTROY

RIDE *create_ride(char *line, int *v);
void destroy_ride(void *v);

// PARSING

GHashTable *read_rides(char *dataset, GHashTable *user_stats, GHashTable *driver_stats, GHashTable *city_stats, GHashTable *drivers, GHashTable *users);

#endif
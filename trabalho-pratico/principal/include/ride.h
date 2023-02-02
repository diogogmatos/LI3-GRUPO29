#ifndef ride_h
#define ride_h

#include <glib.h>
#include "../include/stats.h"

typedef struct ride RIDE;

// FUNÇÕES GET

char *get_ride_id(RIDE *r);
int get_ride_id_int(RIDE *r);
char *get_ride_date(RIDE *r);
char *get_ride_driver(RIDE *r);
int get_ride_driver_int(RIDE *r);
char *get_ride_user(RIDE *r);
char *get_ride_city(RIDE *r);
int get_ride_distance(RIDE *r);
int get_ride_score_user(RIDE *r);
int get_ride_score_driver(RIDE *r);
double get_ride_tip(RIDE *r);

// FUNÇÕES CREATE / DESTROY

RIDE *create_ride(char *line, int *v);
void destroy_ride(void *v);

// PARSING

GHashTable *read_rides(char *dataset, STATS *s, GHashTable *drivers, GHashTable *users);

#endif
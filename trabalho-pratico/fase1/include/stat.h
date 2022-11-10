#ifndef stat_h
#define stat_h

#include "../include/user.h"
#include "../include/driver.h"
#include "../include/catalog.h"
#include <glib.h>

typedef struct stat
{
	char *id;
	char *username;
    GHashTable *drivers;
	GHashTable *users;

	int age;
	double avg_score;
	int trips;
	double money;
	int total_distance;
} STAT;

void stat_build(gpointer key, gpointer value, gpointer userdata);
void init_stat(CATALOG *c, STAT *s);
STAT *create_user_stat(USER *u, CATALOG *c);
STAT *create_driver_stat(DRIVER *d, CATALOG *c);

#endif

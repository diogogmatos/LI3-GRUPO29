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
	char *driver_name;
	CATALOG *c;
	GHashTable *ht;
	char *most_recent_trip;
	double score;

	int age;
	double avg_score;
	int trips;
	double money;
	int total_distance;
} STAT;

STAT *user_stat(USER *u, CATALOG *c);
STAT *driver_stat(DRIVER *d, CATALOG *c);
GHashTable *avg_score_stats(CATALOG *c);

#endif

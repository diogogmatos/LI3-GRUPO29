#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/catalog.h"
#include "../include/utils.h"
#include "../include/stat.h"

void stat_build(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	STAT *s = userdata;

	if (!strcmp(r->user, s->username))
	{
		DRIVER *d = g_hash_table_lookup(s->drivers, r->driver);

		s->avg_score += r->score_user;
		s->trips += 1;
		s->money += r->tip + get_price(d) + get_tax(d) * r->distance;
		s->total_distance += r->distance;
	}

	if (!strcmp(r->driver, s->id))
	{
		s->avg_score += r->score_driver;
		s->trips += 1;
		s->money += r->tip;
		s->total_distance += r->distance;
	}
}

void init_stat(CATALOG *c, STAT *s)
{
	s->trips = 0;
	s->avg_score = 0;
	s->money = 0;

	g_hash_table_foreach(c->rides, stat_build, s);

	s->avg_score /= s->trips;
}

STAT *create_user_stat(USER *u, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT));

	s->username = u->username;
	s->id = " ";
	s->drivers = c->drivers;
	s->users = c->users;
	s->age = get_age(u->birth_date);

	init_stat(c, s);

	return s;
}

STAT *create_driver_stat(DRIVER *d, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT));

	s->id = d->id;
	s->username = " ";
	s->drivers = c->drivers;
	s->users = c->users;
	s->age = get_age(d->birth_day);

	init_stat(c, s);

	s->money += get_price(d) * s->trips + get_tax(d) * s->total_distance;

	return s;
}

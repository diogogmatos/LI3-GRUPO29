#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/ride.h"
#include "../include/utils.h"
#include "../include/city_stats.h"

struct stat
{
    char *city;
    int trips;
    double money;
    double avg_cost;
};

// FUNÇÕES GET

char *get_city_stat_city(CITY_STAT *s)
{
    return strdup(s->city);
}

int get_city_stat_trips(CITY_STAT *s)
{
    return s->trips;
}

double get_city_stat_money(CITY_STAT *s)
{
    return s->money;
}

double get_city_stat_avg_cost(CITY_STAT *s)
{
    return s->avg_cost;
}

// FUNÇÕES DESTROY

void destroy_city_stat(void *v)
{
	CITY_STAT *s = v;

	free(s->city);
	free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_city_stat(RIDE *r, GHashTable *c_stats, GHashTable *drivers)
{
	char *city = get_ride_city(r);
	CITY_STAT *cl = g_hash_table_lookup(c_stats, city);

	char *driver = get_ride_driver(r);
	DRIVER *d = g_hash_table_lookup(drivers, driver);

	int distance = get_ride_distance(r);

	if (cl == NULL)
	{
		CITY_STAT *city_stat = malloc(sizeof(CITY_STAT));

		city_stat->city = city;
		city_stat->trips = 1;
		city_stat->money = get_price(d) + get_tax(d) * distance;
		city_stat->avg_cost = city_stat->money;

		g_hash_table_insert(c_stats, city_stat->city, city_stat);
	}
	else
	{
		cl->trips += 1;
		cl->money += get_price(d) + get_tax(d) * distance;

		cl->avg_cost = cl->money / cl->trips;

		free(city);
	}

	free(driver);
}

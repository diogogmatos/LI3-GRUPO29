#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/ride.h"
#include "../include/utils.h"
#include "../include/driver_stats.h"

struct stat
{
	char *id;
	char *driver_name;
	char *gender;
	int age;
	char *city;
	double score;
	double avg_score;
	int trips;
	double money;
	int total_distance;
	char *most_recent_trip;
};

// FUNÇÕES GET

char *get_driver_stat_id(DRIVER_STAT *s)
{
	return strdup(s->id);
}

char *get_driver_stat_driver_name(DRIVER_STAT *s)
{
	return strdup(s->driver_name);
}

char *get_driver_stat_gender(DRIVER_STAT *s)
{
	return strdup(s->gender);
}

int get_driver_stat_age(DRIVER_STAT *s)
{
	return s->age;
}

char *get_driver_stat_city(DRIVER_STAT *s)
{
	return strdup(s->city);
}

double get_driver_stat_score(DRIVER_STAT *s)
{
	return s->score;
}

double get_driver_stat_avg_score(DRIVER_STAT *s)
{
	return s->avg_score;
}

int get_driver_stat_trips(DRIVER_STAT *s)
{
	return s->trips;
}

double get_driver_stat_money(DRIVER_STAT *s)
{
	return s->money;
}

int get_driver_stat_total_distance(DRIVER_STAT *s)
{
	return s->total_distance;
}

char *get_driver_stat_most_recent_trip(DRIVER_STAT *s)
{
	return strdup(s->most_recent_trip);
}

// FUNÇÕES DESTROY

void destroy_driver_stat(void *v)
{
	DRIVER_STAT *s = v;

	free(s->id);
	free(s->driver_name);
	free(s->gender);
	free(s->city);
	free(s->most_recent_trip);
	free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_driver_stat(RIDE *r, GHashTable *d_stats, GHashTable *drivers)
{
	char *driver = get_ride_driver(r);
	DRIVER *d = g_hash_table_lookup(drivers, driver);
	DRIVER_STAT *dl = g_hash_table_lookup(d_stats, driver);

	int distance = get_ride_distance(r);
	double score_driver = get_ride_score_driver(r);
	double tip = get_ride_tip(r);

	char *account_status = get_driver_account_status(d);

	if (!strcmp(account_status, "active"))
	{
		char *date = get_ride_date(r);

		if (dl == NULL)
		{
			DRIVER_STAT *driver_stat = malloc(sizeof(DRIVER_STAT));

			char *birth_date = get_driver_birth_day(d);

			driver_stat->id = driver;
			driver_stat->driver_name = get_driver_name(d);
			driver_stat->gender = get_driver_gender(d);
			driver_stat->age = get_age(birth_date);
			driver_stat->city = get_ride_city(r);

			driver_stat->score = score_driver;
			driver_stat->avg_score = score_driver;
			driver_stat->trips = 1;
			driver_stat->money = tip + get_price(d) + get_tax(d) * distance;
			driver_stat->total_distance = distance;

			driver_stat->most_recent_trip = date;

			g_hash_table_insert(d_stats, driver_stat->id, driver_stat);

			free(birth_date);
		}
		else
		{
			dl->score += score_driver;
			dl->trips += 1;
			dl->money += tip + get_price(d) + get_tax(d) * distance;
			dl->total_distance += distance;

			if (convert_date(date) > convert_date(dl->most_recent_trip))
			{
				free(dl->most_recent_trip);
				dl->most_recent_trip = date;
			}
			else
				free(date);

			dl->avg_score = dl->score / dl->trips;

			free(driver);
		}
	}
	else
		free(driver);

	free(account_status);
}

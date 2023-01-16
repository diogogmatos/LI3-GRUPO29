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
	int id;
	char *driver_name;
	char *gender;
	int age;
	double score;
	int trips;
	double avg_score;
	double money;
	char *most_recent_trip;
};

// FUNÇÕES GET

char *get_driver_stat_id(DRIVER_STAT *s)
{
	char *id_str = id_to_string(s->id);
	return id_str;
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

char *get_driver_stat_most_recent_trip(DRIVER_STAT *s)
{
	return strdup(s->most_recent_trip);
}

// FUNÇÕES DESTROY

void destroy_driver_stat(void *v)
{
	DRIVER_STAT *s = v;

	free(s->driver_name);
	free(s->gender);
	free(s->most_recent_trip);
	free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_driver_stat(RIDE *r, GHashTable *d_stats, GHashTable *drivers)
{
	int driver = get_ride_driver_int(r);
	DRIVER *d = g_hash_table_lookup(drivers, &driver);
	DRIVER_STAT *dl = g_hash_table_lookup(d_stats, &driver);

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

			driver_stat->score = score_driver;
			driver_stat->avg_score = score_driver;
			driver_stat->trips = 1;
			driver_stat->money = tip + get_price(d) + get_tax(d) * distance;

			driver_stat->most_recent_trip = date;

			g_hash_table_insert(d_stats, &(driver_stat->id), driver_stat);

			free(birth_date);
		}
		else
		{
			dl->score += score_driver;
			dl->trips += 1;
			dl->money += tip + get_price(d) + get_tax(d) * distance;

			if (compare_dates(date, dl->most_recent_trip) > 0)
			{
				free(dl->most_recent_trip);
				dl->most_recent_trip = date;
			}
			else
				free(date);

			dl->avg_score = dl->score / dl->trips;
		}
	}

	free(account_status);
}

/* Função `compare_avg_score()`
 * Responsável por comparar duas estatísticas relativas à avaliação média de um condutor e retornar -1 ou 1 de acordo
 * com o resultado da comparação. É utilizada de forma auxiliar a `g_list_sort()` para ordenar uma lista de STAT's.
 */
gint compare_avg_score(gconstpointer a, gconstpointer b)
{
	DRIVER_STAT *s1 = (DRIVER_STAT *)a;
	DRIVER_STAT *s2 = (DRIVER_STAT *)b;

	int r;

	double avg_score1 = s1->avg_score;
	double avg_score2 = s2->avg_score;

	if (avg_score1 > avg_score2)
		r = -1;
	else if (avg_score1 < avg_score2)
		r = 1;
	else
	{
		char *date1 = s1->most_recent_trip;
		char *date2 = s2->most_recent_trip;

		int dc = compare_dates(date1, date2);

		if (dc > 0)
			r = -1;
		else if (dc < 0)
			r = 1;
		else
		{
			int id1 = s1->id;
			int id2 = s2->id;

			if (id1 < id2)
				r = -1;
			else
				r = 1;
		}
	}

	return r;
}

GList *sort_query2_stats(GHashTable *driver_stats)
{
	GList *list = g_hash_table_get_values(driver_stats);

	list = g_list_sort(list, compare_avg_score);

	return list;
}

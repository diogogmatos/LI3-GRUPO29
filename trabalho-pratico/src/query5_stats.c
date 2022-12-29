#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/ride.h"
#include "../include/utils.h"
#include "../include/catalog.h"
#include "../include/query5_stats.h"

struct stat
{
	char *date_a;
	char *date_b;
	CATALOG *c;

	double money;
	int trips;
};

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void build_query5_stat(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	QUERY5_STAT *s = userdata;

	char *date = get_ride_date(r);

	if (compare_dates(s->date_a, date) <= 0 && compare_dates(date, s->date_b) <= 0) // Apenas considerados os valores de viagens efetuadas entre as datas referidas
	{
		char *id = get_ride_driver(r);
		DRIVER *d = g_hash_table_lookup(get_catalog_drivers(s->c), id);

		int distance = get_ride_distance(r);

		s->money += get_price(d) + get_tax(d) * distance;
		s->trips += 1;

		free(id);
	}
	free(date);
}

double create_query5_stat(char *date_a, char *date_b, CATALOG *c)
{
	QUERY5_STAT *s = malloc(sizeof(QUERY5_STAT));
	double r;

	s->date_a = date_a;
	s->date_b = date_b;
	s->c = c;

	s->money = 0;
	s->trips = 0;

	g_hash_table_foreach(get_catalog_rides(c), build_query5_stat, s);

	r = (double)s->money / (double)s->trips;

	free(s);

	return r;
}

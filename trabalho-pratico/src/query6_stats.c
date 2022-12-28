#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/ride.h"
#include "../include/utils.h"
#include "../include/catalog.h"
#include "../include/query6_stats.h"

struct stat
{
	char* date_a;
	char* date_b;
	char* city;
	CATALOG* c;

	int total_distance;
	int trips;
};

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void build_query6_stat(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	QUERY6_STAT *s = userdata;

	char *date = get_ride_date(r);
	char *city = get_ride_city(r);

	if ((!strcmp(city, s->city)) && (compare_dates(s->date_a, date) <= 0) && (compare_dates(date, s->date_b) <= 0)) // Apenas considerados os valores de viagens efetuadas entre as datas referidas numa determinada cidade
	{
        s->total_distance += get_ride_distance(r);
		s->trips += 1;
	}
    free(date);
    free(city);
}

double create_query6_stat(char *city, char *date_a, char *date_b, CATALOG *c)
{
	QUERY6_STAT *s = malloc(sizeof(QUERY6_STAT)); 
	double r;

	s->date_a = date_a;
	s->date_b = date_b;
	s->city = city;
	s->c = c;

	s->total_distance = 0;
	s->trips = 0;

	g_hash_table_foreach(get_catalog_rides(c), build_query6_stat, s);

	r = (double)s->total_distance / (double)s->trips;

	free(s);

	return r;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/ride.h"
#include "../include/query9_stats.h"
#include "../include/utils.h"

struct stat
{
	int id;
	char *date;
	int distance;
	double tip;
};

struct aux
{
	char *date_a;
	char *date_b;
	GSList *list;
};

// FUNÇÕES GET

char *get_query9_stat_id(QUERY9_STAT *s)
{
	char *id_str = id_to_string(s->id);
	return id_str;
}

int get_query9_stat_id_int(QUERY9_STAT *s)
{
	return s->id;
}

char *get_query9_stat_date(QUERY9_STAT *s)
{
	return strdup(s->date);
}

int get_query9_stat_distance(QUERY9_STAT *s)
{
	return s->distance;
}

double get_query9_stat_tip(QUERY9_STAT *s)
{
	return s->tip;
}

// FUNÇÕES DESTROY

void destroy_query9_stat(void *v)
{
	QUERY9_STAT *s = v;

	free(s->date);
	free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void build_query9_stat(gpointer key, gpointer value, gpointer userdata)
{
	key = key; // Para evitar warnings de variáveis não utilizadas
	
	RIDE *r = value;
	QUERY9_AUX *s = userdata;

	double tip = get_ride_tip(r);
	char *date = get_ride_date(r);

	if (tip > 0 && compare_dates(s->date_a, date) <= 0 && compare_dates(date, s->date_b) <= 0)
	{
		QUERY9_STAT *ride_stat = malloc(sizeof(QUERY9_STAT));

		ride_stat->id = get_ride_id_int(r);
		ride_stat->date = date;
		ride_stat->distance = get_ride_distance(r);
		ride_stat->tip = tip;

		s->list = g_slist_append(s->list, ride_stat);
	}
	else
	{
		free(date);
	}
}

GSList *create_query9_stats(char *date_a, char *date_b, GHashTable *rides)
{
	GSList *r;
	
	QUERY9_AUX *s = malloc(sizeof(QUERY9_AUX));

	s->list = NULL;
	s->date_a = date_a;
	s->date_b = date_b;

	g_hash_table_foreach(rides, build_query9_stat, s);

	r = s->list;
	
	free(s);

	return r;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/catalog.h"
#include "../include/utils.h"
#include "../include/query8_stats.h"

struct stat
{
	char *ride_id;
	char *id;
	char *username;
	int acc_age_d;
	int acc_age_u;
};

struct aux
{
	GSList *list;
	char *gender;
	int age;
	CATALOG *c;
};

// FUNÇÕES GET

char *get_query8_stat_ride_id(QUERY8_STAT *s)
{
	return strdup(s->ride_id);
}

char *get_query8_stat_id(QUERY8_STAT *s)
{
	return strdup(s->id);
}

char *get_query8_stat_username(QUERY8_STAT *s)
{
	return strdup(s->username);
}

int get_query8_stat_acc_age_d(QUERY8_STAT *s)
{
	return s->acc_age_d;
}

int get_query8_stat_acc_age_u(QUERY8_STAT *s)
{
	return s->acc_age_u;
}

// FUNÇÕES DESTROY

void destroy_query8_stat(void *v)
{
	QUERY8_STAT *s = v;

	free(s->id);
	free(s->username);
	free(s->ride_id);
	free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void build_query8_stat(gpointer key, gpointer value, gpointer userdata)
{
	key = key; // Para evitar warnings de variáveis não utilizadas
	
	RIDE *r = value;
	QUERY8_AUX *s = userdata;

	char *id = get_ride_driver(r);
	DRIVER *d = g_hash_table_lookup(get_catalog_drivers(s->c), id);

	char *username = get_ride_user(r);
	USER *u = g_hash_table_lookup(get_catalog_users(s->c), username);

	char *account_status_d = get_driver_account_status(d);
	char *account_status_u = get_user_account_status(u);

	if (!strcmp(account_status_d, "active") && !strcmp(account_status_u, "active"))
	{
		char *genderd = get_driver_gender(d);
		char *genderu = get_user_gender(u);
		char *dated_s = get_driver_account_creation(d);
		char *dateu_s = get_user_account_creation(u);

		int aged = convert_date(dated_s);
		int ageu = convert_date(dateu_s);

		double aged_y = aged / 365.2425;
		double ageu_y = ageu / 365.2425;

		if (!strcmp(genderd, s->gender) && !strcmp(genderu, s->gender) && aged_y >= s->age && ageu_y >= s->age)
		{
			QUERY8_STAT *ride_stat = malloc(sizeof(QUERY8_STAT));

			ride_stat->ride_id = get_ride_id(r);
			ride_stat->id = id;
			ride_stat->username = username;
			ride_stat->acc_age_d = aged;
			ride_stat->acc_age_u = ageu;

			s->list = g_slist_append(s->list, ride_stat);
		}
		else
		{
			free(id);
			free(username);
		}

		free(genderd);
		free(genderu);
		free(dated_s);
		free(dateu_s);
	}
	else
	{
		free(id);
		free(username);
	}

	free(account_status_d);
	free(account_status_u);
}

GSList *create_query8_stats(char *gender, int X, CATALOG *c)
{
	GSList *r;
	
	QUERY8_AUX *s = malloc(sizeof(QUERY8_AUX));

	s->list = NULL;
	s->gender = gender;
	s->age = X;
	s->c = c;

	g_hash_table_foreach(get_catalog_rides(c), build_query8_stat, s);

	r = s->list;

	free(s);

	return r;
}

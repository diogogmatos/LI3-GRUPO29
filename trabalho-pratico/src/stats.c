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

/* Struct STAT
 * Usada nas funções de estatísticas para guardar os dados necessários para a sua execução:
 * Dados de utilizadores, condutores e dados auxiliares.
 */
struct stat
{
	int age;	  // q1,q8
	char *gender; // q1

	char *user_name;	// q3
	int total_distance; // q3

	double avg_cost; // q4
	char *city;		 // q4, q7

	char *id;		  // q1, q2
	char *ride_id;    // q8
	char *username;	  // q1, q3
	double money;	  // q1, q4
	double avg_score; // q1, q2, q7
	int trips;		  // q1, q2, q4, q7

    char *date;        // q5
	char *date_a;     // q5
	char *date_b;     // q5

	int acc_age_u;    // q8
	int acc_age_d;    // q8

	char *most_recent_trip; // q2, q3
	double score;			// q2, q7
	char *driver_name;		// q2, q7
	GHashTable *ht;			// q2, q3, q7

	CATALOG *c; // q1, q2, q3, q4, q7
};

// FUNÇÕES GET

int get_stat_age(STAT *s)
{
	return s->age;
}

double get_stat_money(STAT *s)
{
	return s->money;
}

char *get_stat_gender(STAT *s)
{
	return strdup(s->gender);
}

double get_stat_score(STAT *s)
{
	return s->score;
}

char *get_stat_driver_name(STAT *s)
{
	return strdup(s->driver_name);
}

char *get_stat_user_name(STAT *s)
{
	return strdup(s->user_name);
}

int get_stat_total_distance(STAT *s)
{
	return s->total_distance;
}

char *get_stat_city(STAT *s)
{
	return strdup(s->city);
}

double get_stat_avg_cost(STAT *s)
{
	return s->avg_cost;
}

char *get_stat_date(STAT *s)
{
	return strdup(s->date);
}

char *get_stat_date_a(STAT *s)
{
	return strdup(s->date_a);
}

char *get_stat_date_b(STAT *s)
{
	return strdup(s->date_b);
}

int get_stat_acc_age_d(STAT *s)
{
	return s->acc_age_d;
}

int get_stat_acc_age_u(STAT *s)
{
	return s->acc_age_u;
}

char *get_stat_id(STAT *s)
{
	return strdup(s->id);
}

char *get_stat_ride_id(STAT *s)
{
	return strdup(s->ride_id);
}

double get_stat_avg_score(STAT *s)
{
	return s->avg_score;
}

int get_stat_trips(STAT *s)
{
	return s->trips;
}

char *get_stat_username(STAT *s)
{
	return strdup(s->username);
}

char *get_stat_most_recent_trip(STAT *s)
{
	return strdup(s->most_recent_trip);
}

// FUNÇÕES DESTROY

void destroy_query8_stat(void *v)
{
	STAT *s = v;

	free(s->id);
	free(s->username);
	free(s->ride_id);
	free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

// - calculadas durante o parsing do ficheiro de rides:

// - calculadas percorrendo a tabela das viagens mais uma vez:

void create_query8_stat(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	STAT *s = userdata;

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
			STAT *ride_stat = malloc(sizeof(STAT));

			ride_stat->ride_id = get_ride_id(r);
			ride_stat->id = id;
			ride_stat->username = username;
			ride_stat->acc_age_d = aged;
			ride_stat->acc_age_u = ageu;

			g_hash_table_insert(s->ht, ride_stat->ride_id, ride_stat);
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

void create_query8_stats(GHashTable *query8_stats, char *gender, int X, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT)); 

  s->ht = query8_stats;
	s->gender = gender;
	s->age = X;
	s->c = c;

	g_hash_table_foreach(get_catalog_rides(c), create_query8_stat, s);

	free(s);
}

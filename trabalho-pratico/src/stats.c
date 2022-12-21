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
	int age;	  // q1
	char *gender; // q1

	char *user_name;	// q3
	int total_distance; // q3

	double avg_cost; // q4
	char *city;		 // q4, q7

	char *id;		  // q1, q2
	char *username;	  // q1, q3
	double money;	  // q1, q4
	double avg_score; // q1, q2, q7
	int trips;		  // q1, q2, q4, q7

    char *date;        // q5
	char *date_a;     // q5
	char *date_b;     // q5

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

char *get_stat_id(STAT *s)
{
	return strdup(s->id);
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

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

// - calculadas durante o parsing do ficheiro de rides:

// - calculadas percorrendo a tabela das viagens mais uma vez:

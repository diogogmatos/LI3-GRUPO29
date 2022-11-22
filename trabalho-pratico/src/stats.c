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
	double money; // q1

	double score;	   // q2
	char *driver_name; // q2

	char *user_name;	// q3
	int total_distance; // q3

	char *id;		  // q1, q2
	double avg_score; // q1, q2
	int trips;		  // q1, q2

	char *username; // q1, q3

	char *most_recent_trip; // q2, q3
	GHashTable *ht;			// q2, q3

	CATALOG *c; // q1, q2, q3
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

/* Função `destroy_stat_avg_score()`
 * Responsável por libertar a memória alocada para cada struct STAT na criação da tabela hash de estatísticas
 * de avaliação média, na query 2.
 */
void destroy_stat_avg_score(void *v)
{
	STAT *s = v;

	free(s->driver_name);
	free(s->id);
	free(s->most_recent_trip);
	free(s);
}

/* Função `destroy_stat_tot_dist()`
 * Responsável por libertar a memória alocada para cada struct STAT na criação da tabela hash de estatísticas
 * de distância total, na query 3.
 */
void destroy_stat_tot_dist(void *v)
{
	STAT *s = v;

	free(s->user_name);
	free(s->username);
	free(s->most_recent_trip);
	free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

/* Função `stat_build()`
 * Função que é chamada para todos os valores da tabela hash das viagens.
 * Utilizada como auxiliar de `user_stat()`e `driver_stat()`, é responsável por atualizar os dados da
 * STAT `s` à medida que a tabela hash é percorrida, verificando se o utilizador/condutor da linha atual é
 * o que está a ser analisado.
 */
void stat_build(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	STAT *s = userdata;

	char *user = get_ride_user(r);
	char *driver = get_ride_driver(r);

	int score_user = get_ride_score_user(r);
	int score_driver = get_ride_score_driver(r);
	double tip = get_ride_tip(r);
	int distance = get_ride_distance(r);

	if (!strcmp(user, s->username))
	{
		DRIVER *d = g_hash_table_lookup(s->c->drivers, driver);

		s->avg_score += score_user;
		s->trips += 1;
		s->money += tip + get_price(d) + get_tax(d) * distance;
		s->total_distance += distance;
	}

	if (!strcmp(driver, s->id))
	{
		DRIVER *d = g_hash_table_lookup(s->c->drivers, driver);

		s->avg_score += score_driver;
		s->trips += 1;
		s->money += tip + get_price(d) + get_tax(d) * distance;
		s->total_distance += distance;
	}

	free(user);
	free(driver);
}

/* Função `user_stat()`
 * Responsável por criar as estatístias de um utilizador.
 */
STAT *user_stat(USER *u, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT));
	char *birth_date = get_user_birth_date(u);

	s->username = get_user_username(u);
	s->id = " ";
	s->c = c;
	s->age = get_age(birth_date);
	s->trips = 0;
	s->avg_score = 0;
	s->money = 0;

	g_hash_table_foreach(c->rides, stat_build, s);

	s->avg_score /= s->trips;

	free(birth_date);
	free(s->username);

	return s;
}

/* Função `driver_stat()`
 * Responsável por criar as estatísticas de um condutor.
 */
STAT *driver_stat(DRIVER *d, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT));
	char *birth_day = get_driver_birth_day(d);

	s->id = get_driver_id(d);
	s->username = " ";
	s->c = c;
	s->age = get_age(birth_day);
	s->trips = 0;
	s->avg_score = 0;
	s->money = 0;

	g_hash_table_foreach(c->rides, stat_build, s);

	s->avg_score /= s->trips;

	free(birth_day);
	free(s->id);

	return s;
}

/* Função `avg_score_build()`
 * Função que é chamada para todos os valores da tabela hash das viagens.
 * Utilizada como auxiliar de `avg_score_stats()`, é responsável por incializar a tabela hash `ht`
 * de forma a que, no fim da execução, esta contenha a avaliação média de todos os condutores, ativos, existentes.
 * Para além disso a table hash irá conter também o id, nome, nº de viagens e viagem mais recente de cada condutor. Dados
 * que são necessários para a ordenação das estatísticas e para a impressão dos resultados.
 */
void avg_score_build(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	STAT *s = userdata;

	char *driver_id = get_ride_driver(r);

	DRIVER *d = g_hash_table_lookup(s->c->drivers, driver_id);

	char *account_status = get_driver_account_status(d);

	if (!strcmp(account_status, "active"))
	{
		GHashTable *ht = s->ht;

		STAT *dl = g_hash_table_lookup(ht, driver_id);

		int score_driver = get_ride_score_driver(r);
		char *date = get_ride_date(r);

		if (dl == NULL)
		{
			STAT *driver = malloc(sizeof(STAT));

			driver->id = driver_id;
			driver->driver_name = get_driver_name(d);
			driver->c = s->c;

			driver->score = score_driver;
			driver->most_recent_trip = date;
			driver->trips = 1;
			driver->avg_score = score_driver;

			g_hash_table_insert(ht, driver->id, driver);
		}
		else
		{
			dl->score += score_driver;
			dl->trips += 1;

			if (convert_date(date) > convert_date(dl->most_recent_trip))
			{
				free(dl->most_recent_trip);
				dl->most_recent_trip = date;
			}
			else
				free(date);

			dl->avg_score = dl->score / dl->trips;

			free(driver_id);
		}
	}
	else
	{
		free(driver_id);
	}

	free(account_status);
}

/* Função `avg_score_stats()`
 * Responsável por criar as estatísticas de avaliação média para todos os condutores ativos.
 * Cria uma tabela hash `ht` que guarda estas estatísticas.
 * No fim da execução, liberta a memória alocada para `s`.
 */
void avg_score_stats(GHashTable *ht, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT)); // STAT que serve como transportadora de dados necessários para a função avg_score_build

	s->c = c;	// hash table de drivers
	s->ht = ht; // hash table "ht" vai guardar os drivers e as suas estatísticas

	g_hash_table_foreach(c->rides, avg_score_build, s); // atualiza a hash table "ht" com os drivers e as suas estatísticas

	free(s);
}

/* Função `tot_dist_build()`
 * Função que é chamada para todos os valores da tabela hash das viagens.
 * Utilizada como auxiliar de `tot_dist_stats()`, é responsável por incializar a tabela hash `ht`
 * de forma a que, no fim da execução, esta contenha a distância total para todos os condutores, ativos, existentes.
 * Para além disso a table hash irá conter também o username, nome e viagem mais recente de cada utilizador. Dados
 * que são necessários para a ordenação das estatísticas e para a impressão dos resultados.
 */
void tot_dist_build(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	STAT *s = userdata;

	char *username = get_ride_user(r);

	USER *u = g_hash_table_lookup(s->c->users, username);

	char *account_status = get_user_account_status(u);

	if (!strcmp(account_status, "active"))
	{
		GHashTable *ht = s->ht;

		STAT *ul = g_hash_table_lookup(ht, username);

		char *date = get_ride_date(r);
		int distance = get_ride_distance(r);

		if (ul == NULL)
		{
			STAT *user = malloc(sizeof(STAT));

			user->username = username;
			user->user_name = get_user_name(u);
			user->c = s->c;

			user->most_recent_trip = date;
			user->total_distance = distance;

			g_hash_table_insert(ht, user->username, user);
		}
		else
		{
			ul->total_distance += distance;

			if (convert_date(date) > convert_date(ul->most_recent_trip))
			{
				free(ul->most_recent_trip);
				ul->most_recent_trip = date;
			}
			else
				free(date);

			free(username);
		}
	}
	else
	{
		free(username);
	}

	free(account_status);
}

/* Função `tot_dist_stats()`
 * Responsável por criar as estatísticas de distância total para todos os utilizadores ativos.
 * Cria uma tabela hash `ht` que guarda estas estatísticas.
 * No fim da execução, liberta a memória alocada para `s`.
 */
void tot_dist_stats(GHashTable *ht, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT));

	s->c = c;
	s->ht = ht;

	g_hash_table_foreach(c->rides, tot_dist_build, s);

	free(s);
}

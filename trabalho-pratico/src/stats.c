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

    int date;        // q5
	int date_a;     // q5
	int date_b;     // q5

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

int get_stat_date(STAT *s)
{
	return s->date;
}

int get_stat_date_a(STAT *s)
{
	return s->date_a;
}

int get_stat_date_b(STAT *s)
{
	return s->date_b;
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

void destroy_user_stat(void *v)
{
	STAT *s = v;

	free(s->username);
	free(s->user_name);
	free(s->gender);
	free(s->most_recent_trip);
	free(s);
}

void destroy_driver_stat(void *v)
{
	STAT *s = v;

	free(s->id);
	free(s->driver_name);
	free(s->gender);
	free(s->city);
	free(s->most_recent_trip);
	free(s);
}

void destroy_city_stat(void *v)
{
	STAT *s = v;

	free(s->city);
	free(s);
}

void destroy_query5_stat(void *v)
{
	STAT *s = v;

	free(s->id);
	free(s);
}
void destroy_query7_stat(void *v)
{
	STAT *s = v;

	free(s->id);
	free(s->driver_name);
	free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

// - calculadas durante o parsing do ficheiro de rides:

void create_user_stat(RIDE *r, GHashTable *u_stats, GHashTable *drivers, GHashTable *users)
{
	char *username = get_ride_user(r);
	USER *u = g_hash_table_lookup(users, username);
	STAT *ul = g_hash_table_lookup(u_stats, username);

	int distance = get_ride_distance(r);
	double score_user = get_ride_score_user(r);
	double tip = get_ride_tip(r);

	char *account_status = get_user_account_status(u);

	if (!strcmp(account_status, "active"))
	{
		char *date = get_ride_date(r);

		char *driver = get_ride_driver(r);
		DRIVER *d = g_hash_table_lookup(drivers, driver);

		if (ul == NULL)
		{
			STAT *user_stat = malloc(sizeof(STAT));

			char *birth_date = get_user_birth_date(u);

			user_stat->username = username;
			user_stat->user_name = get_user_name(u);
			user_stat->gender = get_user_gender(u);
			user_stat->age = get_age(birth_date);

			user_stat->score = score_user;
			user_stat->avg_score = score_user;
			user_stat->trips = 1;
			user_stat->money = tip + get_price(d) + get_tax(d) * distance;
			user_stat->total_distance = distance;

			user_stat->most_recent_trip = date;

			g_hash_table_insert(u_stats, user_stat->username, user_stat);

			free(birth_date);
		}
		else
		{
			ul->score += score_user;
			ul->trips += 1;
			ul->money += tip + get_price(d) + get_tax(d) * distance;
			ul->total_distance += distance;

			if (convert_date(date) > convert_date(ul->most_recent_trip))
			{
				free(ul->most_recent_trip);
				ul->most_recent_trip = date;
			}
			else
				free(date);

			free(username);

			ul->avg_score = ul->score / ul->trips;
		}

		free(driver);
	}
	else
		free(username);

	free(account_status);
}

void create_driver_stat(RIDE *r, GHashTable *d_stats, GHashTable *drivers)
{
	char *driver = get_ride_driver(r);
	DRIVER *d = g_hash_table_lookup(drivers, driver);
	STAT *dl = g_hash_table_lookup(d_stats, driver);

	int distance = get_ride_distance(r);
	double score_driver = get_ride_score_driver(r);
	double tip = get_ride_tip(r);

	char *account_status = get_driver_account_status(d);

	if (!strcmp(account_status, "active"))
	{
		char *date = get_ride_date(r);

		if (dl == NULL)
		{
			STAT *driver_stat = malloc(sizeof(STAT));

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

void create_city_stat(RIDE *r, GHashTable *c_stats, GHashTable *drivers)
{
	char *city = get_ride_city(r);
	STAT *cl = g_hash_table_lookup(c_stats, city);

	char *driver = get_ride_driver(r);
	DRIVER *d = g_hash_table_lookup(drivers, driver);

	int distance = get_ride_distance(r);

	if (cl == NULL)
	{
		STAT *city_stat = malloc(sizeof(STAT));

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

void build_query5_stat(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	STAT *s = userdata;

	int date = convert_date(get_ride_date(r));

	if (date >= s->date_a && date <= s->date_b) // Apenas considerados os valores de viagens efetuadas entre as datas referidas
	{
		char *id = get_ride_driver(r);
		DRIVER *d = g_hash_table_lookup(get_catalog_drivers(s->c), id);

		int distance = get_ride_distance(r);

        s->money += get_price(d) + get_tax(d) * distance;
		s->trips += 1;
		s->avg_cost = s->money / s->trips;
	}

}

double create_query5_stat(int date_a, int date_b, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT)); 

	s->date_a = date_a;
	s->date_b = date_b;
	s->c = c;
	s->money = 0;
	s->trips = 0;

	g_hash_table_foreach(get_catalog_rides(c), build_query5_stat, s);

	return s->avg_cost;

}
// - calculadas percorrendo a tabela das viagens mais uma vez:

void create_query7_stat(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	STAT *s = userdata;

	char *city = get_ride_city(r);

	if (!strcmp(city, s->city)) // Apenas considerados os valores de viagens efetuadas na cidade pretendida
	{
		char *id = get_ride_driver(r);
		STAT *dl = g_hash_table_lookup(s->ht, id);

		if (dl == NULL) // Se o condutor ainda não está na tabela hash, inicializamos os dados e adicionamos à tabela
		{
			STAT *driver_stat = malloc(sizeof(STAT));
			DRIVER *d = g_hash_table_lookup(get_catalog_drivers(s->c), id);

			driver_stat->id = id;
			driver_stat->driver_name = get_driver_name(d);

			driver_stat->trips = 1;
			driver_stat->score = get_ride_score_driver(r);
			driver_stat->avg_score = driver_stat->score;

			g_hash_table_insert(s->ht, driver_stat->id, driver_stat);
		}
		else // Se o condutor já está na tabela hash, atualizamos os dados
		{
			dl->trips += 1;
			dl->score += get_ride_score_driver(r);
			dl->avg_score = dl->score / dl->trips;

			free(id);
		}
	}

	free(city);
}

void create_query7_stats(GHashTable *query7_stats, char *city, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT)); // Usada para passar valores à função `create_query7_stat()`

	s->ht = query7_stats;
	s->city = city;
	s->c = c;

	g_hash_table_foreach(get_catalog_rides(c), create_query7_stat, s);

	free(s);
}

/* -- OLD FUNCTIONS -- */

// /* Função `stat_build()`
//  * Função que é chamada para todos os valores da tabela hash das viagens.
//  * Utilizada como auxiliar de `user_stat()`e `driver_stat()`, é responsável por atualizar os dados da
//  * STAT `s` à medida que a tabela hash é percorrida, verificando se o utilizador/condutor da linha atual é
//  * o que está a ser analisado.
//  */
// void stat_build(gpointer key, gpointer value, gpointer userdata)
// {
// 	RIDE *r = value;
// 	STAT *s = userdata;

// 	char *user = get_ride_user(r);
// 	char *driver = get_ride_driver(r);

// 	int score_user = get_ride_score_user(r);
// 	int score_driver = get_ride_score_driver(r);
// 	double tip = get_ride_tip(r);
// 	int distance = get_ride_distance(r);

// 	if (!strcmp(user, s->username))
// 	{
// 		DRIVER *d = g_hash_table_lookup(get_catalog_drivers(s->c), driver);

// 		s->avg_score += score_user;
// 		s->trips += 1;
// 		s->money += tip + get_price(d) + get_tax(d) * distance;
// 		s->total_distance += distance;
// 	}

// 	if (!strcmp(driver, s->id))
// 	{
// 		DRIVER *d = g_hash_table_lookup(get_catalog_drivers(s->c), driver);

// 		s->avg_score += score_driver;
// 		s->trips += 1;
// 		s->money += tip + get_price(d) + get_tax(d) * distance;
// 		s->total_distance += distance;
// 	}

// 	free(user);
// 	free(driver);
// }

// /* Função `user_stat()`
//  * Responsável por criar as estatístias de um utilizador.
//  */
// STAT *user_stat(USER *u, CATALOG *c)
// {
// 	STAT *s = malloc(sizeof(STAT));
// 	char *birth_date = get_user_birth_date(u);

// 	s->username = get_user_username(u);
// 	s->id = " ";
// 	s->c = c;
// 	s->age = get_age(birth_date);
// 	s->trips = 0;
// 	s->avg_score = 0;
// 	s->money = 0;

// 	g_hash_table_foreach(get_catalog_rides(c), stat_build, s);

// 	s->avg_score /= s->trips;

// 	free(birth_date);
// 	free(s->username);

// 	return s;
// }

// /* Função `driver_stat()`
//  * Responsável por criar as estatísticas de um condutor.
//  */
// STAT *driver_stat(DRIVER *d, CATALOG *c)
// {
// 	STAT *s = malloc(sizeof(STAT));
// 	char *birth_day = get_driver_birth_day(d);

// 	s->id = get_driver_id(d);
// 	s->username = " ";
// 	s->c = c;
// 	s->age = get_age(birth_day);
// 	s->trips = 0;
// 	s->avg_score = 0;
// 	s->money = 0;

// 	g_hash_table_foreach(get_catalog_rides(c), stat_build, s);

// 	s->avg_score /= s->trips;

// 	free(birth_day);
// 	free(s->id);

// 	return s;
// }

// /* Função `avg_score_build()`
//  * Função que é chamada para todos os valores da tabela hash das viagens.
//  * Utilizada como auxiliar de `avg_score_stats()`, é responsável por incializar a tabela hash `ht`
//  * de forma a que, no fim da execução, esta contenha a avaliação média de todos os condutores, ativos, existentes.
//  * Para além disso a table hash irá conter também o id, nome, nº de viagens e viagem mais recente de cada condutor. Dados
//  * que são necessários para a ordenação das estatísticas e para a impressão dos resultados.
//  */
// void avg_score_build(gpointer key, gpointer value, gpointer userdata)
// {
// 	RIDE *r = value;
// 	STAT *s = userdata;

// 	char *driver_id = get_ride_driver(r);

// 	DRIVER *d = g_hash_table_lookup(get_catalog_drivers(s->c), driver_id);

// 	char *account_status = get_driver_account_status(d);

// 	if (!strcmp(account_status, "active"))
// 	{
// 		GHashTable *ht = s->ht;

// 		STAT *dl = g_hash_table_lookup(ht, driver_id);

// 		int score_driver = get_ride_score_driver(r);
// 		char *date = get_ride_date(r);

// 		if (dl == NULL)
// 		{
// 			STAT *driver = malloc(sizeof(STAT));

// 			driver->id = driver_id;
// 			driver->driver_name = get_driver_name(d);
// 			driver->c = s->c;

// 			driver->score = score_driver;
// 			driver->most_recent_trip = date;
// 			driver->trips = 1;
// 			driver->avg_score = score_driver;

// 			g_hash_table_insert(ht, driver->id, driver);
// 		}
// 		else
// 		{
// 			dl->score += score_driver;
// 			dl->trips += 1;

// 			if (convert_date(date) > convert_date(dl->most_recent_trip))
// 			{
// 				free(dl->most_recent_trip);
// 				dl->most_recent_trip = date;
// 			}
// 			else
// 				free(date);

// 			dl->avg_score = dl->score / dl->trips;

// 			free(driver_id);
// 		}
// 	}
// 	else
// 	{
// 		free(driver_id);
// 	}

// 	free(account_status);
// }

// /* Função `avg_score_stats()`
//  * Responsável por criar as estatísticas de avaliação média para todos os condutores ativos.
//  * Cria uma tabela hash `ht` que guarda estas estatísticas.
//  * No fim da execução, liberta a memória alocada para `s`.
//  */
// void avg_score_stats(GHashTable *ht, CATALOG *c)
// {
// 	STAT *s = malloc(sizeof(STAT)); // STAT que serve como transportadora de dados necessários para a função avg_score_build

// 	s->c = c;	// hash table de drivers
// 	s->ht = ht; // hash table "ht" vai guardar os drivers e as suas estatísticas

// 	g_hash_table_foreach(get_catalog_rides(c), avg_score_build, s); // atualiza a hash table "ht" com os drivers e as suas estatísticas

// 	free(s);
// }

// /* Função `tot_dist_build()`
//  * Função que é chamada para todos os valores da tabela hash das viagens.
//  * Utilizada como auxiliar de `tot_dist_stats()`, é responsável por incializar a tabela hash `ht`
//  * de forma a que, no fim da execução, esta contenha a distância total para todos os condutores, ativos, existentes.
//  * Para além disso a table hash irá conter também o username, nome e viagem mais recente de cada utilizador. Dados
//  * que são necessários para a ordenação das estatísticas e para a impressão dos resultados.
//  */
// void tot_dist_build(gpointer key, gpointer value, gpointer userdata)
// {
// 	RIDE *r = value;
// 	STAT *s = userdata;

// 	char *username = get_ride_user(r);

// 	USER *u = g_hash_table_lookup(get_catalog_users(s->c), username);

// 	char *account_status = get_user_account_status(u);

// 	if (!strcmp(account_status, "active"))
// 	{
// 		GHashTable *ht = s->ht;

// 		STAT *ul = g_hash_table_lookup(ht, username);

// 		char *date = get_ride_date(r);
// 		int distance = get_ride_distance(r);

// 		if (ul == NULL)
// 		{
// 			STAT *user = malloc(sizeof(STAT));

// 			user->username = username;
// 			user->user_name = get_user_name(u);
// 			user->c = s->c;

// 			user->most_recent_trip = date;
// 			user->total_distance = distance;

// 			g_hash_table_insert(ht, user->username, user);
// 		}
// 		else
// 		{
// 			ul->total_distance += distance;

// 			if (convert_date(date) > convert_date(ul->most_recent_trip))
// 			{
// 				free(ul->most_recent_trip);
// 				ul->most_recent_trip = date;
// 			}
// 			else
// 				free(date);

// 			free(username);
// 		}
// 	}
// 	else
// 	{
// 		free(username);
// 	}

// 	free(account_status);
// }

// /* Função `tot_dist_stats()`
//  * Responsável por criar as estatísticas de distância total para todos os utilizadores ativos.
//  * Cria uma tabela hash `ht` que guarda estas estatísticas.
//  * No fim da execução, liberta a memória alocada para `s`.
//  */
// void tot_dist_stats(GHashTable *ht, CATALOG *c)
// {
// 	STAT *s = malloc(sizeof(STAT));

// 	s->c = c;
// 	s->ht = ht;

// 	g_hash_table_foreach(get_catalog_rides(c), tot_dist_build, s);

// 	free(s);
// }

// /* Função `destroy_stat_avg_score()`
//  * Responsável por libertar a memória alocada para cada struct STAT na criação da tabela hash de estatísticas
//  * de avaliação média, na query 2.
//  */
// void destroy_stat_avg_score(void *v)
// {
// 	STAT *s = v;

// 	free(s->driver_name);
// 	free(s->id);
// 	free(s->most_recent_trip);
// 	free(s);
// }

// FUNÇÕES DESTROY

// /* Função `destroy_stat_tot_dist()`
//  * Responsável por libertar a memória alocada para cada struct STAT na criação da tabela hash de estatísticas
//  * de distância total, na query 3.
//  */
// void destroy_stat_tot_dist(void *v)
// {
// 	STAT *s = v;

// 	free(s->user_name);
// 	free(s->username);
// 	free(s->most_recent_trip);
// 	free(s);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/user_stats.h"
#include "../include/utils.h"

struct stat
{
	char *username;
	char *user_name;
	char *gender;
	int age;
	double score;
	double avg_score;
	int trips;
	double money;
	int total_distance;
	char *most_recent_trip;
};

// FUNÇÕES GET

char *get_user_stat_username(USER_STAT *s)
{
	return strdup(s->username);
}

char *get_user_stat_user_name(USER_STAT *s)
{
	return strdup(s->user_name);
}

char *get_user_stat_gender(USER_STAT *s)
{
	return strdup(s->gender);
}

int get_user_stat_age(USER_STAT *s)
{
	return s->age;
}

double get_user_stat_score(USER_STAT *s)
{
	return s->score;
}

double get_user_stat_avg_score(USER_STAT *s)
{
	return s->avg_score;
}

int get_user_stat_trips(USER_STAT *s)
{
	return s->trips;
}

double get_user_stat_money(USER_STAT *s)
{
	return s->money;
}

int get_user_stat_total_distance(USER_STAT *s)
{
	return s->total_distance;
}

char *get_user_stat_most_recent_trip(USER_STAT *s)
{
	return strdup(s->most_recent_trip);
}

// FUNÇÕES DESTROY

void destroy_user_stat(void *v)
{
	USER_STAT *s = v;

	free(s->username);
	free(s->user_name);
	free(s->gender);
	free(s->most_recent_trip);
	free(s);
}

// FUNÇÕES DE CRIAÇÃO DE ESTATÍSTICAS

void create_user_stat(RIDE *r, GHashTable *u_stats, GHashTable *drivers, GHashTable *users)
{
	char *username = get_ride_user(r);
	USER *u = g_hash_table_lookup(users, username);
	USER_STAT *ul = g_hash_table_lookup(u_stats, username);

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
			USER_STAT *user_stat = malloc(sizeof(USER_STAT));

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

			if (compare_dates(date, ul->most_recent_trip) > 0)
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

/* Função `compare_tot_dist()`
 * Responsável por comparar duas estatísticas relativas à distância total de um utilizador e retornar -1 ou 1 de acordo
 * com o resultado da comparação. É utilizada de forma auxiliar a `g_list_sort()` para ordenar uma lista de STAT's.
 */
gint compare_tot_dist(gconstpointer a, gconstpointer b)
{
	USER_STAT *s1 = (USER_STAT *)a;
	USER_STAT *s2 = (USER_STAT *)b;

	int r;

	int distance1 = s1->total_distance;
	int distance2 = s2->total_distance;

	if (distance1 > distance2)
		r = -1;
	else if (distance1 < distance2)
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
			char *username1 = s1->username;
			char *username2 = s2->username;

			r = strcmp(username1, username2);
		}
	}

	return r;
}

GList *sort_query3_stats(GHashTable *user_stats)
{
	GList *list = g_hash_table_get_values(user_stats);

	list = g_list_sort(list, compare_tot_dist);

	return list;
}

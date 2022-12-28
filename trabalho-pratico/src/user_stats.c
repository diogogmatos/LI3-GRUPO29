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

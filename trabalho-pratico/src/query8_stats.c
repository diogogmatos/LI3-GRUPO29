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
	char *gender;
	char *ride;
	double driver_acc_age;
	double user_acc_age;
};

char *get_query8_stat_gender(QUERY8_STAT *s)
{
	return strdup(s->gender);
}

char *get_query8_stat_ride(QUERY8_STAT *s)
{
	return strdup(s->ride);
}

double get_query8_stat_driver_acc_age(QUERY8_STAT *s)
{
	return s->driver_acc_age;
}

double get_query8_stat_user_acc_age(QUERY8_STAT *s)
{
	return s->user_acc_age;
}

void destroy_query8_stat(void *v)
{
	QUERY8_STAT *s = v;

	free(s->gender);
	free(s->ride);
	free(s);
}

void create_query8_stats(RIDE *r, GHashTable *query8_stats, GHashTable *drivers, GHashTable *users)
{
	char *driver = get_ride_driver(r);
	char *user = get_ride_user(r);

	DRIVER *d = g_hash_table_lookup(drivers, driver);
	USER *u = g_hash_table_lookup(users, user);

	char *driver_acc_status = get_driver_account_status(d);
	char *user_acc_status = get_user_account_status(u);

	if (!strcmp(driver_acc_status, "active") && !strcmp(user_acc_status, "active"))
	{
		char *driver_gender = get_driver_gender(d);
		char *user_gender = get_user_gender(u);

		if (!strcmp(user_gender, driver_gender))
		{
			QUERY8_STAT *s = malloc(sizeof(QUERY8_STAT));

			char *driver_acc_creation = get_driver_account_creation(d);
			char *user_acc_creation = get_user_account_creation(u);

			s->gender = driver_gender;
			s->ride = get_ride_id(r);
			s->driver_acc_age = convert_date(driver_acc_creation) / 365.2425;
			s->user_acc_age = convert_date(user_acc_creation) / 365.2425;

			g_hash_table_insert(query8_stats, s->ride, s);

			free(driver_acc_creation);
			free(user_acc_creation);
		}
		else
			free(driver_gender);

		free(user_gender);
	}

	free(driver);
	free(user);
	free(driver_acc_status);
	free(user_acc_status);
}

gint compare_query8_stats(gconstpointer a, gconstpointer b)
{
	QUERY8_STAT *s1 = (QUERY8_STAT *)a;
	QUERY8_STAT *s2 = (QUERY8_STAT *)b;

	int r;

	double age1_d = s1->driver_acc_age;
	double age2_d = s2->driver_acc_age;

	if (age1_d > age2_d)
		r = -1;
	else if (age1_d < age2_d)
		r = 1;
	else
	{
		double age1_u = s1->user_acc_age;
		double age2_u = s2->user_acc_age;

		if (age1_u > age2_u)
			r = -1;
		else if (age1_u < age2_u)
			r = 1;
		else
		{
			char *id1 = s1->ride;
			char *id2 = s2->ride;

			r = strcmp(id1, id2);
		}
	}

	return r;
}

GList *sort_query8_stats(GHashTable *query8_stats)
{
	GList *list = g_hash_table_get_values(query8_stats);

	list = g_list_sort(list, compare_query8_stats);

	return list;
}

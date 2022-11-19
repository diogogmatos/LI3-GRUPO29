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

void stat_build(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	STAT *s = userdata;

	if (!strcmp(r->user, s->username))
	{
		DRIVER *d = g_hash_table_lookup(s->c->drivers, r->driver);

		s->avg_score += r->score_user;
		s->trips += 1;
		s->money += r->tip + get_price(d) + get_tax(d) * r->distance;
		s->total_distance += r->distance;
	}

	if (!strcmp(r->driver, s->id))
	{
		DRIVER *d = g_hash_table_lookup(s->c->drivers, r->driver);

		s->avg_score += r->score_driver;
		s->trips += 1;
		s->money += r->tip + get_price(d) + get_tax(d) * r->distance;
		s->total_distance += r->distance;
	}
}

STAT *user_stat(USER *u, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT));

	s->username = u->username;
	s->id = "\0";
	s->c = c;
	s->age = get_age(u->birth_date);
	s->trips = 0;
	s->avg_score = 0;
	s->money = 0;

	g_hash_table_foreach(c->rides, stat_build, s);

	s->avg_score /= s->trips;

	return s;
}

STAT *driver_stat(DRIVER *d, CATALOG *c)
{
	STAT *s = malloc(sizeof(STAT));

	s->id = d->id;
	s->username = "\0";
	s->c = c;
	s->age = get_age(d->birth_day);
	s->trips = 0;
	s->avg_score = 0;
	s->money = 0;

	g_hash_table_foreach(c->rides, stat_build, s);

	s->avg_score /= s->trips;

	return s;
}

void destroy_stat(void *v)
{
	STAT *s = v;
	free(s);
}

void avg_score_build(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	STAT *s = userdata;

	GHashTable *ht = s->ht;									   // hash table "ht" que vai guardando os drivers e as suas estatísticas à medida que percorre as rides
	DRIVER *d = g_hash_table_lookup(s->c->drivers, r->driver); // procura o driver na hash table de drivers para obter o seu nome

	if (!strcmp(d->account_status, "active")) // apenas executa se o driver for ativo
	{
		STAT *driver = malloc(sizeof(STAT)); // STAT que vai guardar as estatísticas do driver pedidas na query

		driver->id = r->driver;
		driver->driver_name = d->name;
		driver->c = s->c; // o catálogo de hash tables terá de ser usado na função "compare_avg_score" que apenas recebe dois valores de "ht"

		STAT *dl = g_hash_table_lookup(ht, r->driver); // procura o driver na "ht"

		if (dl == NULL) // se o driver não estiver na "ht"
		{
			driver->score = r->score_driver;
			driver->most_recent_trip = r->date;
			driver->trips = 1;
		}
		else // se o driver já estiver na "ht"
		{
			driver->score = dl->score + r->score_driver;
			driver->trips = dl->trips + 1;

			/* compara as datas da ride atual com a mais recente da "ht" de modo a ficar com a data da trip mais recente
			 * de cada driver, que é usada em "compare_avg_score" */
			if (convert_date(r->date) > convert_date(dl->most_recent_trip))
				driver->most_recent_trip = r->date;
			else
				driver->most_recent_trip = dl->most_recent_trip;
		}

		driver->avg_score = driver->score / driver->trips;

		g_hash_table_insert(ht, driver->id, driver);
	}
}

GHashTable *avg_score_stats(CATALOG *c)
{
	GHashTable *ht = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_stat);

	STAT *s = malloc(sizeof(STAT)); // STAT que serve como transportadora de dados necessários para a função avg_score_build

	s->c = c;	// hash table de drivers
	s->ht = ht; // hash table "ht" vai guardar os drivers e as suas estatísticas

	g_hash_table_foreach(c->rides, avg_score_build, s); // atualiza a hash table "ht" com os drivers e as suas estatísticas

	free(s);

	return ht;
}

void tot_dist_build(gpointer key, gpointer value, gpointer userdata)
{
	RIDE *r = value;
	STAT *s = userdata;

	GHashTable *ht = s->ht;
	USER *u = g_hash_table_lookup(s->c->users, r->user);

	if (!strcmp(u->account_status, "active"))
	{
		STAT *user =malloc(sizeof(STAT));

		user->username = r->user;
		user->user_name = u->name;
		user->c = s->c;

		STAT *ul = g_hash_table_lookup(ht, r->user);

		if (ul == NULL)
		{
			user->most_recent_trip = r->date;
			user->total_distance = r->distance;
		}
		else
		{
			user->total_distance = ul->total_distance + r->distance; 

			if (convert_date(r->date) > convert_date(ul->most_recent_trip))
				user->most_recent_trip = r->date;
			else
				user->most_recent_trip = ul->most_recent_trip;
		}

		g_hash_table_insert(ht, user->username, user);
	}
}

GHashTable *tot_dist_stats(CATALOG *c)
{
	GHashTable *ht = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_stat); 

	STAT *s = malloc(sizeof(STAT));

	s->c = c;
	s->ht = ht;

	g_hash_table_foreach(c->rides, tot_dist_build, s);

	free(s);

	return ht;
}

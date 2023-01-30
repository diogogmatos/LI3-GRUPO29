#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/io.h"
#include "../include/queries.h"
#include "../include/catalog.h"
#include "../include/utils.h"
#include "../include/user_stats.h"
#include "../include/driver_stats.h"
#include "../include/city_stats.h"
#include "../include/query5_stats.h"
#include "../include/query6_stats.h"
#include "../include/query7_stats.h"
#include "../include/query8_stats.h"
#include "../include/query9_stats.h"

// QUERY 1

/* Função `query_1()`
 * Responsável por interpretar, criar e imprimir as estatísticas pedidas na query 1.
 * Para condutores, chama a função `driver_stat()` e para utilizadores, a função `user_stat()`, que
 * criam a struct STAT com as estatísticas pedidas.
 * No fim da execução, liberta a memória alocada.
 */
void query_1(int is_id, char *value, char *path, CATALOG *c)
{
    if (is_id != 0) // driver
    {
        char *id = value;
        int id_int = atoi(id);
        DRIVER *d = g_hash_table_lookup(get_catalog_drivers(c), &id_int);

        FILE *f;
        if (path != NULL)
            f = fopen(path, "w");
        else
            f = NULL;

        if (d == NULL)
        {
            fclose(f);
            return;
        }

        char *account_status = get_driver_account_status(d);

        if (!strcmp(account_status, "active")) // se a conta for ativa executa normalmente
        {
            DRIVER_STAT *s = g_hash_table_lookup(get_catalog_driver_stats(c), &id_int);

            char *name = get_driver_stat_driver_name(s);
            char *gender = get_driver_stat_gender(s);

            int age = get_driver_stat_age(s);
            double avg_score = get_driver_stat_avg_score(s);
            int trips = get_driver_stat_trips(s);
            double money = get_driver_stat_money(s);

            if (path != NULL)
                fprintf(f, "%s;%s;%d;%.3f;%d;%.3f\n", name, gender, age, avg_score, trips, money);
            else
                printf("%s;%s;%d;%.3f;%d;%.3f\n", name, gender, age, avg_score, trips, money);

            free(name);
            free(gender);
        }

        if (path != NULL) fclose(f);
        free(account_status);
    }
    else // user
    {
        char *username = value;
        USER *u = g_hash_table_lookup(get_catalog_users(c), username);

        FILE *f = fopen(path, "w");

        if (u == NULL)
        {
            fclose(f);
            return;
        }

        char *account_status = get_user_account_status(u);

        if (!strcmp(account_status, "active"))
        {
            USER_STAT *s = g_hash_table_lookup(get_catalog_user_stats(c), username);

            char *name = get_user_stat_user_name(s);
            char *gender = get_user_stat_gender(s);

            int age = get_user_stat_age(s);
            double avg_score = get_user_stat_avg_score(s);
            int trips = get_user_stat_trips(s);
            double money = get_user_stat_money(s);

            fprintf(f, "%s;%s;%d;%.3f;%d;%.3f\n", name, gender, age, avg_score, trips, money);

            free(name);
            free(gender);
        }

        fclose(f);
        free(account_status);
    }
}

// QUERY 2

/* Função `query_2()`
 * Responsável por interpretar, criar e imprimir as estatísticas pedidas na query 2.
 * Chama a função `avg_score_stats()` para criar a tabela hash com as estatísticas pedidas.
 * Coloca os valores da tabela hash `stats` numa lista `l` e ordena a lista de acordo com
 * as instruções dadas no enunciado, com ajuda da função `compare_avg_score()`.
 * No fim da execução, liberta a memória alocada (incluindo a lista e a tabela hash).
 */
void query_2(int N, char *path, CATALOG *c)
{
    FILE *f = fopen(path, "w");

    if (N <= 0)
    {
        fclose(f);
        return;
    }

    GList *list = get_catalog_query2_stats(c);

    int acc;
    GList *iterator;
    for (acc = 0, iterator = list; acc < N && iterator; ++acc, iterator = iterator->next)
    {
        char *id = get_driver_stat_id(iterator->data);
        char *driver_name = get_driver_stat_driver_name(iterator->data);

        double avg_score = get_driver_stat_avg_score(iterator->data);

        fprintf(f, "%s;%s;%.3f\n", id, driver_name, avg_score);

        free(id);
        free(driver_name);
    }

    fclose(f);
}

// QUERY 3

/* Função `query_3()`
 * Responsável por interpretar, criar e imprimir as estatísticas pedidas na query 3.
 * Chama a função `tot_dist_stats()` para criar a tabela hash com as estatísticas pedidas.
 * Coloca os valores da tabela hash `stats` numa lista `l` e ordena a lista de acordo com
 * as instruções dadas no enunciado, com ajuda da função `compare_tot_dist()`.
 * No fim da execução, liberta a memória alocada (incluindo a lista e a tabela hash).
 */
void query_3(int N, char *path, CATALOG *c)
{
    FILE *f = fopen(path, "w");

    if (N <= 0)
    {
        fclose(f);
        return;
    }

    GList *list = get_catalog_query3_stats(c);

    int acc;
    GList *iterator;
    for (acc = 0, iterator = list; acc < N && iterator; ++acc, iterator = iterator->next)
    {
        char *username = get_user_stat_username(iterator->data);
        char *user_name = get_user_stat_user_name(iterator->data);
        int tot_dist = get_user_stat_total_distance(iterator->data);

        fprintf(f, "%s;%s;%d\n", username, user_name, tot_dist);

        free(username);
        free(user_name);
    }

    fclose(f);
}

// QUERY 4

void query_4(char *city, char *path, CATALOG *c)
{
    CITY_STAT *s = g_hash_table_lookup(get_catalog_city_stats(c), city);

    FILE *f = fopen(path, "w");

    if (s == NULL)
    {
        fclose(f);
        return;
    }

    double avg_cost = get_city_stat_avg_cost(s);

    fprintf(f, "%.3f\n", avg_cost);

    fclose(f);
}

// QUERY 5

void query_5(char *date_a, char *date_b, char *path, CATALOG *c)
{
    double avg_cost = create_query5_stat(date_a, date_b, c);

    FILE *f = fopen(path, "w");

    if (avg_cost < 0)
    {
        fclose(f);
        return;
    }

    fprintf(f, "%.3f\n", avg_cost);

    fclose(f);
}

// QUERY 6

void query_6(char *city, char *date_a, char *date_b, char *path, CATALOG *c)
{
    double avg_distance = create_query6_stat(city, date_a, date_b, c);

    FILE *f = fopen(path, "w");

    if (avg_distance < 0)
    {
        fclose(f);
        return;
    }

    fprintf(f, "%.3f\n", avg_distance);

    fclose(f);
}

// QUERY 7

void query_7(int N, char *city, char *path, CATALOG *c)
{
    GList *list = get_catalog_query7_stats(c);

    FILE *f = fopen(path, "w");

    int acc;
    GList *iterator;
    for (acc = 0, iterator = list; acc < N && iterator; iterator = iterator->next)
    {
        char *citydriver = get_query7_stat_citydriver(iterator->data);

        char *city_l = strsep(&citydriver, "-");

        if (!strcmp(city_l, city))
        {
            char *id = strsep(&citydriver, "\0");
            int id_int = atoi(id);
            char *driver_name = get_driver_stat_driver_name(g_hash_table_lookup(get_catalog_drivers(c), &id_int));
            double avg_score = get_query7_stat_avg_score(iterator->data);

            fprintf(f, "%s;%s;%.3f\n", id, driver_name, avg_score);

            acc++;

            free(driver_name);
        }

        free(city_l);
    }

    fclose(f);
}

// QUERY 8

void query_8(char *gender, int X, char *path, CATALOG *c)
{
    GList *query8_stats = get_catalog_query8_stats(c);

    FILE *f = fopen(path, "w");

    GList *iterator;
    for (iterator = query8_stats; iterator; iterator = iterator->next)
    {
        char *gender_l = get_query8_stat_gender(iterator->data);
        double driver_acc_age = get_query8_stat_driver_acc_age(iterator->data);
        double user_acc_age = get_query8_stat_user_acc_age(iterator->data);

        if (!strcmp(gender_l, gender) && driver_acc_age >= X && user_acc_age >= X)
        {
            int ride = get_query8_stat_ride(iterator->data);
            char *driver = get_ride_driver(g_hash_table_lookup(get_catalog_rides(c), &ride));
            int driver_int = atoi(driver);
            char *driver_name = get_driver_name(g_hash_table_lookup(get_catalog_drivers(c), &driver_int));
            char *user = get_ride_user(g_hash_table_lookup(get_catalog_rides(c), &ride));
            char *user_name = get_user_name(g_hash_table_lookup(get_catalog_users(c), user));

            fprintf(f, "%s;%s;%s;%s\n", driver, driver_name, user, user_name);

            free(driver);
            free(driver_name);
            free(user);
            free(user_name);
        }

        free(gender_l);
    }

    fclose(f);
}

// QUERY 9

gint compare_query9_rides(gconstpointer a, gconstpointer b)
{
    QUERY9_STAT *s1 = (QUERY9_STAT *)a;
    QUERY9_STAT *s2 = (QUERY9_STAT *)b;

    int r;

    int distance1 = get_query9_stat_distance(s1);
    int distance2 = get_query9_stat_distance(s2);

    if (distance1 > distance2)
        r = -1;
    else if (distance1 < distance2)
        r = 1;
    else
    {
        char *date1 = get_query9_stat_date(s1);
        char *date2 = get_query9_stat_date(s2);

        if (compare_dates(date1, date2) > 0)
            r = -1;
        else if (compare_dates(date1, date2) < 0)
            r = 1;
        else
        {
            int id1 = get_query9_stat_id_int(s1);
            int id2 = get_query9_stat_id_int(s2);

            if (id1 < id2)
                r = 1;
            else
                r = -1;
        }

        free(date1);
        free(date2);
    }

    return r;
}

void query_9(char *date_a, char *date_b, char *path, CATALOG *c)
{
    GSList *query9_stats = create_query9_stats(date_a, date_b, c);
    query9_stats = g_slist_sort(query9_stats, compare_query9_rides);

    FILE *f = fopen(path, "w");

    GSList *iterator;
    for (iterator = query9_stats; iterator; iterator = iterator->next)
    {
        char *id = get_query9_stat_id(iterator->data);
        int id_int = atoi(id);
        char *date = get_query9_stat_date(iterator->data);
        int distance = get_query9_stat_distance(iterator->data);
        char *city = get_ride_city(g_hash_table_lookup(get_catalog_rides(c), &id_int));
        double tip = get_query9_stat_tip(iterator->data);

        fprintf(f, "%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);

        free(id);
        free(date);
        free(city);
    }

    fclose(f);

    g_slist_free_full(query9_stats, destroy_query9_stat);
}

// QUERY INVÁLIDA

/* Função `invalid_query()`
 * Responsável por criar um ficheiro .txt de output vazio para uma query inválida.
 */
void invalid_query(char *path)
{
    FILE *f = fopen(path, "w");
    fclose(f);
}

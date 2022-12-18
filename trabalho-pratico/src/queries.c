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
#include "../include/stat.h"
#include "../include/utils.h"

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
        DRIVER *d = g_hash_table_lookup(get_catalog_drivers(c), id);

        FILE *f = fopen(path, "w");

        if (d == NULL)
        {
            fclose(f);
            return;
        }

        char *account_status = get_driver_account_status(d);

        if (!strcmp(account_status, "active")) // se a conta for ativa executa normalmente
        {
            STAT *s = g_hash_table_lookup(get_catalog_driver_stats(c), id);

            char *name = get_stat_driver_name(s);
            char *gender = get_stat_gender(s);

            int age = get_stat_age(s);
            double avg_score = get_stat_avg_score(s);
            int trips = get_stat_trips(s);
            double money = get_stat_money(s);

            fprintf(f, "%s;%s;%d;%.3f;%d;%.3f\n", name, gender, age, avg_score, trips, money);

            free(name);
            free(gender);
        }

        fclose(f);
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
            STAT *s = g_hash_table_lookup(get_catalog_user_stats(c), username);

            char *name = get_stat_user_name(s);
            char *gender = get_stat_gender(s);

            int age = get_stat_age(s);
            double avg_score = get_stat_avg_score(s);
            int trips = get_stat_trips(s);
            double money = get_stat_money(s);

            fprintf(f, "%s;%s;%d;%.3f;%d;%.3f\n", name, gender, age, avg_score, trips, money);

            free(name);
            free(gender);
        }

        fclose(f);
        free(account_status);
    }
}

// QUERY 2

/* Função `compare_avg_score()`
 * Responsável por comparar duas estatísticas relativas à avaliação média de um condutor e retornar -1 ou 1 de acordo
 * com o resultado da comparação. É utilizada de forma auxiliar a `g_list_sort()` para ordenar uma lista de STAT's.
 */
gint compare_avg_score(gconstpointer a, gconstpointer b)
{
    STAT *s1 = (STAT *)a;
    STAT *s2 = (STAT *)b;

    int r;

    double avg_score1 = get_stat_avg_score(s1);
    double avg_score2 = get_stat_avg_score(s2);

    if (avg_score1 > avg_score2)
        r = -1;
    else if (avg_score1 < avg_score2)
        r = 1;
    else
    {
        char *date1 = get_stat_most_recent_trip(s1);
        char *date2 = get_stat_most_recent_trip(s2);

        int da = convert_date(date1);
        int db = convert_date(date2);

        free(date1);
        free(date2);

        char *id1 = get_stat_id(s1);
        char *id2 = get_stat_id(s2);

        if (da > db)
            r = -1;
        else if (da < db)
            r = 1;
        else
            r = strcmp(id1, id2);

        free(id1);
        free(id2);
    }

    return r;
}

/* Função `query_2()`
 * Responsável por interpretar, criar e imprimir as estatísticas pedidas na query 2.
 * Chama a função `avg_score_stats()` para criar a tabela hash com as estatísticas pedidas.
 * Coloca os valores da tabela hash `stats` numa lista `l` e ordena a lista de acordo com
 * as instruções dadas no enunciado, com ajuda da função `compare_avg_score()`.
 * No fim da execução, liberta a memória alocada (incluindo a lista e a tabela hash).
 */
void query_2(int N, char *path, CATALOG *c)
{
    GList *list = g_hash_table_get_values(get_catalog_driver_stats(c)); // retorna os valores da hash table "ht" para uma lista
    list = g_list_sort(list, compare_avg_score);                        // ordena a lista por ordem decrescente de average score, tendo em conta as situações de desempate do enunciado

    FILE *f = fopen(path, "w");

    int acc;
    STAT *stat;
    for (acc = 0, stat = g_list_nth_data(list, acc); acc < N && stat != NULL; ++acc, stat = g_list_nth_data(list, acc))
    {
        char *id = get_stat_id(stat);
        char *driver_name = get_stat_driver_name(stat);

        double avg_score = get_stat_avg_score(stat);

        fprintf(f, "%s;%s;%.3f\n", id, driver_name, avg_score);

        free(id);
        free(driver_name);
    }

    fclose(f);

    g_list_free(list);
}

// QUERY 3

/* Função `compare_tot_dist()`
 * Responsável por comparar duas estatísticas relativas à distância total de um utilizador e retornar -1 ou 1 de acordo
 * com o resultado da comparação. É utilizada de forma auxiliar a `g_list_sort()` para ordenar uma lista de STAT's.
 */
gint compare_tot_dist(gconstpointer a, gconstpointer b)
{
    STAT *s1 = (STAT *)a;
    STAT *s2 = (STAT *)b;

    int r;

    int distance1 = get_stat_total_distance(s1);
    int distance2 = get_stat_total_distance(s2);

    if (distance1 > distance2)
        r = -1;
    else if (distance1 < distance2)
        r = 1;
    else
    {
        char *date1 = get_stat_most_recent_trip(s1);
        char *date2 = get_stat_most_recent_trip(s2);

        int da = convert_date(date1);
        int db = convert_date(date2);

        free(date1);
        free(date2);

        char *username1 = get_stat_username(s1);
        char *username2 = get_stat_username(s2);

        if (da > db)
            r = -1;
        else if (da < db)
            r = 1;
        else
            r = strcmp(username1, username2);

        free(username1);
        free(username2);
    }

    return r;
}

/* Função `query_3()`
 * Responsável por interpretar, criar e imprimir as estatísticas pedidas na query 3.
 * Chama a função `tot_dist_stats()` para criar a tabela hash com as estatísticas pedidas.
 * Coloca os valores da tabela hash `stats` numa lista `l` e ordena a lista de acordo com
 * as instruções dadas no enunciado, com ajuda da função `compare_tot_dist()`.
 * No fim da execução, liberta a memória alocada (incluindo a lista e a tabela hash).
 */
void query_3(int N, char *path, CATALOG *c)
{
    GList *list = g_hash_table_get_values(get_catalog_user_stats(c));
    list = g_list_sort(list, compare_tot_dist);

    FILE *f = fopen(path, "w");

    int acc;
    STAT *stat;
    for (acc = 0, stat = g_list_nth_data(list, acc); acc < N && stat != NULL; ++acc, stat = g_list_nth_data(list, acc))
    {
        char *username = get_stat_username(stat);
        char *user_name = get_stat_user_name(stat);
        int tot_dist = get_stat_total_distance(stat);

        fprintf(f, "%s;%s;%d\n", username, user_name, tot_dist);

        free(username);
        free(user_name);
    }

    fclose(f);

    g_list_free(list);
}

// QUERY 4

void query_4(char *city, char *path, CATALOG *c)
{
    STAT *s = g_hash_table_lookup(get_catalog_city_stats(c), city);

    FILE *f = fopen(path, "w");

    if (s == NULL)
    {
        fclose(f);
        return;
    }

    double avg_cost = get_stat_avg_cost(s);

    fprintf(f, "%.3f\n", avg_cost);

    fclose(f);
}

// QUERY 5

void query_5(char *date_a, char *date_b, char *path, CATALOG *c)
{
    double avg_cost = create_query5_stat(date_a, date_b, c);

    FILE *f = fopen(path, "w");

    fprintf(f, "%.3f\n", avg_cost);

    fclose(f);
}


// QUERY 7

gint compare_avg_score_city(gconstpointer a, gconstpointer b)
{
    STAT *s1 = (STAT *)a;
    STAT *s2 = (STAT *)b;

    int r;

    double avg_score1 = get_stat_avg_score(s1);
    double avg_score2 = get_stat_avg_score(s2);

    if (avg_score1 > avg_score2)
        r = -1;
    else if (avg_score1 < avg_score2)
        r = 1;
    else
    {
        char *id1 = get_stat_id(s1);
        char *id2 = get_stat_id(s2);

        if (strcmp(id1, id2) > 0)
            r = -1;
        else
            r = 1;

        free(id1);
        free(id2);
    }

    return r;
}

void query_7(int N, char *city, char *path, CATALOG *c)
{
    GHashTable *query7_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_query7_stat);
    create_query7_stats(query7_stats, city, c);

    GList *list = g_hash_table_get_values(query7_stats);
    list = g_list_sort(list, compare_avg_score_city);

    FILE *f = fopen(path, "w");

    int acc;
    STAT *stat;
    for (acc = 0, stat = g_list_nth_data(list, acc); acc < N && stat != NULL; ++acc, stat = g_list_nth_data(list, acc)) 
    {
        char *id = get_stat_id(stat);
        char *driver_name = get_stat_driver_name(stat);
        double avg_score = get_stat_avg_score(stat);

        fprintf(f, "%s;%s;%.3f\n", id, driver_name, avg_score);

        free(id);
        free(driver_name);
    }

    fclose(f);

    g_list_free(list);
    g_hash_table_destroy(query7_stats);
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/parsing.h"
#include "../include/io.h"
#include "../include/queries.h"
#include "../include/catalog.h"
#include "../include/stat.h"
#include "../include/utils.h"

/* Função `query_1()`
 * Responsável por interpretar, criar e imprimir as estatísticas pedidas na query 1.
 * Para condutores, chama a função `driver_stat()` e para utilizadores, a função `user_stat()`, que
 * criam a struct STAT com as estatísticas pedidas.
 * No fim da execução, liberta a memória alocada.
 */
void query_1(char *input, CATALOG *c, int i)
{
    int is_id = atoi(input);

    if (is_id != 0) // driver
    {
        char *id = strsep(&input, "\n");
        DRIVER *d = g_hash_table_lookup(c->drivers, id);

        char *path = malloc(sizeof(char) * 50);
        sprintf(path, "Resultados/command%d_output.txt", i);

        FILE *f = fopen(path, "a");

        if (!strcmp(d->account_status, "active")) // se a conta for ativa executa normalmente
        {
            STAT *s = driver_stat(d, c);

            fprintf(f, "%s;%s;%d;%.3f;%d;%.3f\n", d->name, d->gender, s->age, s->avg_score, s->trips, s->money);

            free(s);
        }

        fclose(f);
        free(path);
    }
    else // user
    {
        char *username = strsep(&input, "\n");
        USER *u = g_hash_table_lookup(c->users, username);

        char *path = malloc(sizeof(char) * 50);
        sprintf(path, "Resultados/command%d_output.txt", i);

        FILE *f = fopen(path, "a");

        if (!strcmp(u->account_status, "active"))
        {
            STAT *s = user_stat(u, c);

            fprintf(f, "%s;%s;%d;%.3f;%d;%.3f\n", u->name, u->gender, s->age, s->avg_score, s->trips, s->money);

            free(s);
        }

        fclose(f);
        free(path);
    }
}

gint compare_avg_score(gconstpointer a, gconstpointer b)
{
    STAT *s1 = (STAT *)a;
    STAT *s2 = (STAT *)b;

    if (s1->avg_score > s2->avg_score)
        return -1;
    else if (s1->avg_score < s2->avg_score)
        return 1;
    else
    {
        int da = convert_date(s1->most_recent_trip);
        int db = convert_date(s2->most_recent_trip);

        if (da > db)
            return -1;
        else if (da < db)
            return 1;
        else if (s1->id > s2->id)
            return -1;
        else
            return 1;
    }
}

/* Função `query_2()`
 * Responsável por interpretar, criar e imprimir as estatísticas pedidas na query 2.
 * Chama a função `avg_score_stats()` para criar a tabela hash com as estatísticas pedidas.
 * Coloca os valores da tabela hash `stats` numa lista `l` e ordena a lista de acordo com
 * as instruções dadas no enunciado, com ajuda da função `compare_avg_score()`.
 * No fim da execução, liberta a memória alocada (incluindo a lista e a tabela hash).
 */
void query_2(char *input, CATALOG *c, int i)
{
    int N = atoi(input);

    GHashTable *stats = avg_score_stats(c);

    GList *list = g_hash_table_get_values(stats); // retorna os valores da hash table "stats" para uma lista
    list = g_list_sort(list, compare_avg_score);  // ordena a lista por ordem decrescente de average score, tendo em conta as situações de desempate do enunciado

    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "Resultados/command%d_output.txt", i);

    FILE *f = fopen(path, "a");

    int acc;
    for (acc = 0; acc < N; ++acc)
    {
        STAT *s = g_list_nth_data(list, acc);
        fprintf(f, "%s;%s;%.3f\n", s->id, s->driver_name, s->avg_score);
    }

    fclose(f);

    free(path);
    g_list_free(list);
    g_hash_table_destroy(stats);
}

gint compare_tot_dist(gconstpointer a, gconstpointer b)
{
    STAT *s1 = (STAT *)a;
    STAT *s2 = (STAT *)b;

    if (s1->total_distance > s2->total_distance)
        return -1;
    else if (s1->total_distance < s2->total_distance)
        return 1;
    else
    {
        int da = convert_date(s1->most_recent_trip);
        int db = convert_date(s2->most_recent_trip);

        if (da > db)
            return -1;
        else if (da < db)
            return 1;
        else if (strcmp(s1->username, s2->username) > 0)
            return -1;
        else
            return 1;
    }
}

void query_3(char *input, CATALOG *c, int i)
{
    int N = atoi(input);

    GHashTable *stats = tot_dist_stats(c);

    GList *list = g_hash_table_get_values(stats);
    list = g_list_sort(list, compare_tot_dist);

    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "Resultados/command%d_output.txt", i);
    FILE *f = fopen(path, "a");

    int acc;
    for (acc = 0; acc < N; ++acc)
    {
        STAT *s = g_list_nth_data(list, acc);
        fprintf(f, "%s;%s;%d\n", s->username, s->user_name, s->total_distance);
    }

    fclose(f);

    free(path);
    g_list_free(list);
    g_hash_table_destroy(stats);
}

/* Função `invalid_query()`
 * Responsável por criar um ficheiro .txt de output vazio para uma query inválida.
 */
void invalid_query(int i)
{
    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "Resultados/command%d_output.txt", i);

    FILE *f = fopen(path, "a");
    fclose(f);

    free(path);
}

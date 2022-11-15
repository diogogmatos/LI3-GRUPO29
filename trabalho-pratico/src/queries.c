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
        else // caso contrário deixa o ficheiro vazio
        {
            fprintf(f, "\0");
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
        else
        {
            fprintf(f, "\0");
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

void invalid_query(int i)
{
    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "Resultados/command%d_output.txt", i);

    FILE *f = fopen(path, "a");

    fprintf(f, "\n");

    fclose(f);

    free(path);
}

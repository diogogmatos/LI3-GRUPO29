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

void query_1(char *input, CATALOG *c, int i)
{
    int is_id = atoi(input);

    if (is_id != 0)
    {
        char *id = strsep(&input, "\n");
        DRIVER *d = g_hash_table_lookup(c->drivers, id);
        STAT *s = create_driver_stat(d, c);

        char *path = malloc(sizeof(char) * 50);
        sprintf(path, "../Resultados/command%d_output.txt", i);

        FILE *f = fopen(path, "a");

        fprintf(f, "%s;%c;%d;%.3f;%d;%.3f\n", d->name, d->gender, s->age, s->avg_score, s->trips, s->money);

        fclose(f);
    }
    else
    {
        char *username = strsep(&input, "\n");
        USER *u = g_hash_table_lookup(c->users, username);
        STAT *s = create_user_stat(u, c);

        char *path = malloc(sizeof(char) * 50);
        sprintf(path, "../Resultados/command%d_output.txt", i);

        FILE *f = fopen(path, "a");

        fprintf(f, "%s;%c;%d;%.3f;%d;%.3f\n", u->name, u->gender, s->age, s->avg_score, s->trips, s->money);

        fclose(f);
    }
}

void query_2(char *input, CATALOG *c, int i)
{
    printf("[Query 2] - %d | input: %s\n", i, input);
}

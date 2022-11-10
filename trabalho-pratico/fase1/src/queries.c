#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/parsing.h"
#include "../include/io.h"
#include "../include/queries.h"
#include "../include/catalog.h"

void query_1(char *input, CATALOG *c)
{
    if (atoi(input) != 0)
    {
    }
    else
    {
        char *username = strsep(&input, "\n");
        USER *u = g_hash_table_lookup(c->users, username);

        printf("%s;%c\n", u->name, u->gender);
    }
}

void query_2(char *input, CATALOG *c)
{
    printf("query 2");
    printf(" - %s", input);
}

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/parsing.h"
#include "../include/io.h"
#include "../include/catalog.h"

int main(int argc, char **argv)
{
    CATALOG *c = create_catalog();
    char *input = malloc(sizeof(char) * BUFSIZ);

    if (fgets(input, BUFSIZ, stdin) != NULL)
    {
        int query = atoi(strsep(&input, " "));
        handle_input(query, input, c);
    }

    // int key = 1000000;
    // RIDE *ride = g_hash_table_lookup(c->rides, &key);
    // printf("%s\n", ride->comment);
    // return 0;
}

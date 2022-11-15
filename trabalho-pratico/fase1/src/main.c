#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/io.h"
#include "../include/catalog.h"
#include "../include/ride.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("[ERRO] - Falta de argumentos.\n");
    }

    char *dataset = argv[1];
    char *input = argv[2];

    CATALOG *c = create_catalog(dataset);

    FILE *file = fopen(input, "r");
    // "../exemplos_de_queries/tests_2/input.txt"

    char *line = NULL;
    size_t len = 0;

    int i;
    for (i = 1; getline(&line, &len, file) != -1; ++i)
    {
        int query = line[0] - '0';
        char *args = line + 2;
        handle_input(query, args, c, i);
    }

    fclose(file);

    free(line);
    g_hash_table_destroy(c->drivers);
    g_hash_table_destroy(c->users);
    g_hash_table_destroy(c->rides);
    free(c);

    return 0;
}

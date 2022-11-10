#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/io.h"
#include "../include/queries.h"
#include "../include/catalog.h"

void handle_input(int query, char *input, CATALOG *c)
{
    switch (query)
    {
        case 1:
            query_1(input, c);
            return;
        case 2:
            query_2(input, c);
            return;
        default:
            printf("ERRO - Query Inexistente: %d\n", query);
            return;
    }
}

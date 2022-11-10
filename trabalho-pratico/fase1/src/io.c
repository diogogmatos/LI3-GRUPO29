#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/io.h"
#include "../include/queries.h"
#include "../include/catalog.h"

void handle_input(int query, char *input, CATALOG *c, int i)
{
    switch (query)
    {
    case 1:
        query_1(input, c, i);
        return;
    case 2:
        query_2(input, c, i);
        return;
    default:
        printf("[Query Inexistente] - %d | input: %s\n", query, input);
        return;
    }
}

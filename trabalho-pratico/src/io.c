#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/io.h"
#include "../include/queries.h"
#include "../include/catalog.h"

/* Função `handle_input()`
 * Responsável por receber um inteiro `query` com o nº da query a ser executada e uma string `input` com o input dado
 * para essa mesma query e chamar a função correta para lidar com a mesma.
 */
void handle_input(int query, char *input, CATALOG *c, int i)
{
    switch (query)
    {
    case 1:
        query_1(input, c, i);
        printf("Output %d - [OK]\n", i);
        return;
    case 2:
        query_2(input, c, i);
        printf("Output %d - [OK]\n", i);
        return;
    case 3:
        query_3(input, c, i);
        printf("Output %d - [OK]\n", i);
        return;
    default:
        invalid_query(i);
        printf("Output %d - [ERRO: Query Inexistente %d]\n", i, query);
        return;
    }
}

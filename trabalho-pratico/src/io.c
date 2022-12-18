#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/io.h"
#include "../include/queries.h"
#include "../include/catalog.h"
#include "../include/utils.h"

/* Função `handle_input()`
 * Responsável por receber um inteiro `query` com o nº da query a ser executada e uma string `input` com o input dado
 * para essa mesma query e chamar a função correta para lidar com a mesma.
 */
void handle_input(int query, char *input, CATALOG *c, int i)
{
    switch (query)
    {
    case 1:
    {
        int is_id = atoi(input);
        char *value = strsep(&input, "\n");
        char *path = get_results_path(i);

        query_1(is_id, value, path, c);
        printf("Output %d - [OK]\n", i);

        free(path);
        return;
    }
    case 2:
    {
        int N = atoi(input);
        char *path = get_results_path(i);

        query_2(N, path, c);
        printf("Output %d - [OK]\n", i);

        free(path);
        return;
    }
    case 3:
    {
        int N = atoi(input);
        char *path = get_results_path(i);

        query_3(N, path, c);
        printf("Output %d - [OK]\n", i);

        free(path);
        return;
    }
    case 4:
    {
        char *city = strsep(&input, "\n");
        char *path = get_results_path(i);

        query_4(city, path, c);
        printf("Output %d - [OK]\n", i);

        free(path);
        return;
    }
    case 5:
    {
        int date_a = convert_date(strsep(&input, "\n"));
        int date_b = convert_date(strsep(&input, "\n"));
        char *path = get_results_path(i);

        query_5(date_a, date_b, path, c);
        printf("Output %d - [OK]\n", i);

        free(path);
        return;
    }
    case 7:
    {
        int N = atoi(strsep(&input, " "));
        char *city = strsep(&input, "\n");
        char *path = get_results_path(i);

        query_7(N, city, path, c);
        printf("Output %d - [OK]\n", i);

        free(path);
        return;
    }
    default:
    {
        char *path = get_results_path(i);

        invalid_query(path);
        printf("Output %d - [ERRO: Query Inexistente %d]\n", i, query);

        free(path);
        return;
    }
    }
}

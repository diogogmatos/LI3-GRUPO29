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
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 2:
    {
        int N = atoi(input);
        
        char *path = get_results_path(i);

        query_2(N, path, c);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 3:
    {
        int N = atoi(input);
        
        char *path = get_results_path(i);

        query_3(N, path, c);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 4:
    {
        char *city = strsep(&input, "\n");
        
        char *path = get_results_path(i);

        query_4(city, path, c);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 5:
    {
        char *date_a = strsep(&input, " ");
        char *date_b = strsep(&input, "\n");
        
        char *path = get_results_path(i);

        query_5(date_a, date_b, path, c);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 6:
    {
        char *city = strsep(&input, " ");
        char *date_a = strsep(&input, " ");
        char *date_b = strsep(&input, "\n");
        
        char *path = get_results_path(i);

        query_6(city, date_a, date_b, path, c);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 7:
    {
        int N = atoi(strsep(&input, " "));
        char *city = strsep(&input, "\n");
        
        char *path = get_results_path(i);

        query_7(N, city, path, c);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 8:
    {
        char *gender = strsep(&input, " ");
        int X = atoi(strsep(&input, "\n"));
        
        char *path = get_results_path(i);

        query_8(gender, X, path, c);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 9:
    {
        char *date_a = strsep(&input, " ");
        char *date_b = strsep(&input, "\n");
        
        char *path = get_results_path(i);

        query_9(date_a, date_b, path, c);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    default:
    {
        char *path = get_results_path(i);

        invalid_query(path);
        printf("Output %d - Query %d - [ERRO: Query Inexistente]", i, query);

        free(path);
        return;
    }
    }
}

void run_queries(char *dataset, char *input)
{
    clock_t start, end;

    start = clock();
    printf("\n");
    CATALOG *c = create_catalog(dataset, 1);
    end = clock();

    print_loading_time(start, end, "TOTAL"); // Tempo de carregamento do catálogo
    printf("\n");

    FILE *file = fopen(input, "r");

    char *line = NULL;
    size_t len = 0;

    int i;
    for (i = 1; getline(&line, &len, file) != -1; ++i)
    {
        int query = line[0] - '0';
        char *args = line + 2;

        start = clock();
        handle_input(query, args, c, i);
        end = clock();

        print_query_time(start, end); // Tempo de execução da query
    }

    fclose(file);

    free(line);
    destroy_catalog(c);

    print_time_and_memory();
}

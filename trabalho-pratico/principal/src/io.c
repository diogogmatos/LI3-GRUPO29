#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/io.h"
#include "../include/queries.h"
#include "../include/utils.h"
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/stats.h"

/* Função `handle_input()`
 * Responsável por receber um inteiro `query` com o nº da query a ser executada e uma string `input` com o input dado
 * para essa mesma query e chamar a função correta para lidar com a mesma.
 */
void handle_input(int query, char *input, GHashTable *d, GHashTable *u, GHashTable *r, STATS *s, int i)
{
    switch (query)
    {
    case 1:
    {
        int is_id = atoi(input);
        char *value = strsep(&input, "\n");

        char *path = get_results_path(i);

        query_1(is_id, value, path, d, u, s);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 2:
    {
        int N = atoi(input);
        
        char *path = get_results_path(i);

        query_2(N, path, s);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 3:
    {
        int N = atoi(input);
        
        char *path = get_results_path(i);

        query_3(N, path, s);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 4:
    {
        char *city = strsep(&input, "\n");
        
        char *path = get_results_path(i);

        query_4(city, path, s);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 5:
    {
        char *date_a = strsep(&input, " ");
        char *date_b = strsep(&input, "\n");
        
        char *path = get_results_path(i);

        query_5(date_a, date_b, path, s);
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

        query_6(city, date_a, date_b, path, s);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 7:
    {
        int N = atoi(strsep(&input, " "));
        char *city = strsep(&input, "\n");
        
        char *path = get_results_path(i);

        query_7(N, city, path, d, s);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 8:
    {
        char *gender = strsep(&input, " ");
        int X = atoi(strsep(&input, "\n"));
        
        char *path = get_results_path(i);

        query_8(gender, X, path, d, u, r, s);
        printf("Output %d - Query %d - [OK]", i, query);

        free(path);
        return;
    }
    case 9:
    {
        char *date_a = strsep(&input, " ");
        char *date_b = strsep(&input, "\n");
        
        char *path = get_results_path(i);

        query_9(date_a, date_b, path, r);
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
    clock_t start, end, s, e;

    start = clock();
    printf("\n");

    s = clock();
    GHashTable *drivers = read_drivers(dataset);
    e = clock();

    print_loading_time(s, e, "DRIVERS"); // Tempo de carregamento dos condutores

    s = clock();
    GHashTable *users = read_users(dataset);
    e = clock();

    print_loading_time(s, e, "USERS"); // Tempo de carregamento dos utilizadores

    s = clock();
    STATS *stats = create_stats(dataset);
    GHashTable *rides = read_rides(dataset, stats, drivers, users);
    e = clock();

    print_loading_time(s, e, "RIDES"); // Tempo de carregamento das viagens

    s = clock();
    sort_stats(stats);
    e = clock();

    print_loading_time(s, e, "SORTING STATS"); // Tempo de ordenação de estatísticas

    end = clock();

    print_loading_time(start, end, "TOTAL"); // Tempo de carregamento total
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
        handle_input(query, args, drivers, users, rides, stats, i);
        end = clock();

        print_query_time(start, end); // Tempo de execução da query
    }

    fclose(file);

    free(line);
    
    g_hash_table_destroy(drivers);
    g_hash_table_destroy(users);
    g_hash_table_destroy(rides);
    destroy_stats(stats);

    print_time_and_memory();
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glib.h>
#include "../include/io.h"
#include "../include/catalog.h"
#include "../include/utils.h"

/* Função `main()`
 * Recebe 2 argumentos, o primeiro é o caminho para o dataset a ser utilizado e o segundo é o
 * caminho para o ficheiro de input a ser executado. Cria o catálogo de dados, lê o ficheiro de input
 * linha a linha e chama a função `handle_input()` para lidar com cada uma das queries.
 * No fim da execução, liberta a memória alocada para o catálogo de dados e para a string `line` usada
 * em `getline()`.
 */
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("[ERRO] - Falta de argumentos.\n");
    }

    char *dataset = argv[1];
    char *input = argv[2];

    clock_t start, end;

    start = clock();
    printf("\n");
    CATALOG *c = create_catalog(dataset);
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

    return 0;
}

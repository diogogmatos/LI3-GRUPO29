#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/io.h"
#include "../include/catalog.h"
#include "../include/ride.h"

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

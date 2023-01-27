#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função `get_results_path()`
 * Responsável por obter o caminho para o ficheiro de resultados de um comando `i`.
 */
char *get_results_path(int i)
{
    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "Resultados/command%d_output.txt", i);

    return path;
}

char *get_tests_path(int i, char *folder)
{
    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "%s/command%d_output.txt", folder, i);

    return path;
}

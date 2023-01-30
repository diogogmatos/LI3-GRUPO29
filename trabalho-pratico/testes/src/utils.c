#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#include "../../principal/include/utils.h"

char *get_tests_path(int i, char *folder)
{
    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "%s/command%d_output.txt", folder, i);

    return path;
}

void test_results(char *input, char *test_path)
{
    FILE *input_file = fopen(input, "r");

    char *line = NULL;
    size_t len = 0;

    int i, v[1] = {1};
    FILE *produced_file, *expected_file;
    for (i = 1; getline(&line, &len, input_file) != -1; ++i)
    {
        v[0] = 1;

        int query = line[0] - '0';
        char *args = line + 2;

        printf("Teste %d - Query %d:", i, query);
        
        produced_file = fopen(get_results_path(i), "r");
        expected_file = fopen(get_tests_path(i, test_path), "r");

        char *results_line = NULL;
        size_t results_len = 0;

        char *tests_line = NULL;
        size_t tests_len = 0;

        int j;
        for (j = 1; getline(&results_line, &results_len, produced_file) != -1 && getline(&tests_line, &tests_len, expected_file) != -1; ++j)
        {
            if (strcmp(results_line, tests_line))
            {
                if (v[0]) printf("\n");
                printf("\n[ERRO] - Linha %d\n", j);
                printf("Resultado esperado: %s", tests_line);
                printf("Resultado obtido: %s", results_line);
                v[0] = 0;
            }
        }

        fclose(produced_file);
        fclose(expected_file);

        free(results_line);
        free(tests_line);

        if (v[0])
            printf(" [OK]\n");
        else
            printf("\nArgumentos: %s\n", args);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/utils.h"
#include "../../principal/include/io.h"

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("[ERRO] - Falta de argumentos.\n");
        printf("Uso: %s <path para dataset> <path para input> <path para testes>\n", argv[0]);
        return 1;
    }

    char *dataset = argv[1];
    char *input = argv[2];
    char *test_path = argv[3];

    // Avaliação de Desempenho

    run_queries(dataset, input);

    // Teste de Resultados

    test_results(input, test_path);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glib.h>
#include <ncurses.h>
#include "../include/io.h"
#include "../include/catalog.h"
#include "../include/utils.h"
#include "../include/interactive.h"

/* Função `main()`
 * Recebe 2 argumentos, o primeiro é o caminho para o dataset a ser utilizado e o segundo é o
 * caminho para o ficheiro de input a ser executado. Cria o catálogo de dados, lê o ficheiro de input
 * linha a linha e chama a função `handle_input()` para lidar com cada uma das queries.
 * No fim da execução, liberta a memória alocada para o catálogo de dados e para a string `line` usada
 * em `getline()`.
 */
int main(int argc, char **argv)
{   
    if (argc == 1)
    {
        run_interactive();
        return 0;
    }
    
    if (argc < 3)
    {
        printf("[ERRO] - Falta de argumentos.\n");
        printf("Uso: %s <path para dataset> <path para input>\n", argv[0]);
        return 1;
    }

    run_queries(argv[1], argv[2]);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "../include/interactive.h"
#include "../include/utils.h"
#include "../include/catalog.h"
#include "../include/io.h"

typedef struct query
{
    char *description;
    char *arguments;
    char *output;
    char *example;
} QUERY;

QUERY *query_info()
{
    QUERY *queries = malloc(sizeof(QUERY) * 9);

    queries[0].description = "Lista o resumo de um perfil registado no serviço através do seu identificador, representado por <ID>.";
    queries[0].arguments = "<ID> - Identificador do perfil (ID de condutor / USERNAME de utilizador)";
    queries[0].output = "nome;genero;idade;avaliacao_media;numero_viagens;total_gasto";
    queries[0].example = "João;M;23;4.5;10;100";

    queries[1].description = "";
    queries[1].arguments = "";
    queries[1].output = "";
    queries[1].example = "";

    // queries[2] ...

    return queries;
}

char *menu_inicial()
{
    int valid;
    char *dataset = malloc(sizeof(char) * 50);
    
    do
    {
        printf
        (
            "\n| --------- > MODO INTERATIVO --------- |\n"
            "| Por favor introduza o caminho para os |\n"
            "| ficheiros de entrada.                 |\n"
            "| ------------------------------------- |\n\n"
            "> "
        );

        scanf("%s", dataset);

        char *path = get_dataset_path(dataset, "drivers");
        FILE *file = fopen(path, "r");
        
        if (file == NULL)
        {
            valid = 0;
            printf("[ERRO] - Caminho inválido.\n");
        }
        else
        {
            valid = 1;
            fclose(file);
        }

        free(path);
    }
    while (!valid);

    return dataset;
}

int menu_queries()
{
    int sel, valid;
    
    do
    {
        printf
        (
            "\n| -------- SELECIONE UMA QUERY -------- |\n"
            "| 1 - Query 1                           |\n"
            "| 2 - Query 2                           |\n"
            "| 3 - Query 3                           |\n"
            "| 4 - Query 4                           |\n"
            "| 5 - Query 5                           |\n"
            "| 6 - Query 6                           |\n"
            "| 7 - Query 7                           |\n"
            "| 8 - Query 8                           |\n"
            "| 9 - Query 9                           |\n"
            "| ------------------------------------- |\n"
            "| 0 - Sair                              |\n"
            "| ------------------------------------- |\n"
            "|   (Escolha uma query para + info.)    |\n\n"
            "> "
        );

        scanf("%d", &sel);

        if (sel < 0 || sel > 9)
        {
            valid = 0;
            printf("[ERRO] - Query inválida.\n");
        }
        else
            valid = 1;
    }
    while (!valid);

    return sel;
}

int menu_query(int query, QUERY *queries)
{
    int sel, valid;
    
    do
    {
        printf
        (
            "\n| ------------ > QUERY 1 < ------------ |\n"
            "|\n"
            "| > %s\n"
            "|\n"
            "| ARGUMENTOS: %s\n"
            "| OUTPUT: %s\n"
            "| EXEMPLO: %s\n"
            "|\n"
            "| 0 - Voltar\n"
            "| 1 - Executar\n"
            "|\n"
            "| ---/\n\n"
            "> ",
            queries[query-1].description,
            queries[query-1].arguments,
            queries[query-1].output,
            queries[query-1].example
        );

        scanf("%d", &sel);

        if (sel != 0 && sel != 1)
        {
            valid = 0;
            printf("[ERRO] - Escolha inválida.\n");
        }
        else
            valid = 1;
    }
    while (!valid);

    return sel;
}

void execute_query(int query, CATALOG *c)
{
    printf
    (
        "\n| Introduza o(s) argumento(s) para a query %d:\n\n"
        "> ",
        query
    );

    char *args = malloc(sizeof(char) * 50);
    scanf("%s", args);

    int is_id = atoi(args);
    printf("\n");
    if (is_id != 0)
    {
        char *id = id_to_string(is_id);
        handle_input(query, id, c, 0);
        free(id);
    }
    else
    {
        handle_input(query, args, c, 0);
    }
    printf("\n");

    free(args);
}

int handle_query(int query, QUERY *queries, CATALOG *c)
{
    switch (query)
    {
        case 1:
            if (menu_query(1, queries))
                execute_query(query, c);
            return 1;
        default:
            printf("[ERRO] - Query não implementada.\n");
            return 1;
    }
}

void run_interactive()
{
    char *dataset = menu_inicial();

    printf("\nCARREGANDO CATÁLOGO DE DADOS...\n\n");
    CATALOG *c = create_catalog(dataset);
    printf("\nFEITO!\n");

    free(dataset);

    QUERY *queries = query_info();

    int query, voltar;
    do
    {
        query = menu_queries();
        if (query == 0) return;

        voltar = handle_query(query, queries, c);
    }
    while (voltar);
}
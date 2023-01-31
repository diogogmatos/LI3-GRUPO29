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

    queries[1].description = "Lista os N condutores com maior avaliação média.";
    queries[1].arguments = "<N> - Número de condutores a ser listados.";
    queries[1].output = "nome;genero;idade;avaliacao_media;numero_viagens;total_gasto";
    queries[1].example = "000000008899;Rafaela de Barros;3.564";

    queries[2].description = "Lista os N utilizadores com maior distância viajada.";
    queries[2].arguments = "<N> - Número de utilizadores a ser listados.";
    queries[2].output = "username;nome;distancia_total";
    queries[2].example = "Anita-PetPinto38;Anita-Petra Pinto;240";
    
    queries[3].description = "Preço médio das viagens (sem considerar gorjetaas) numa determinada cidade.";
    queries[3].arguments = "<city> - Nome da cidade.";
    queries[3].output = "preco_medio";
    queries[3].example = "10.057";
    
    queries[4].description = "Preço médio das viagens (sem considerar gorjetas) num dado intervalo de tempo.";
    queries[4].arguments = "<data A> <data B> - Datas entre as quais a query atua.";
    queries[4].output = "preco_medio";
    queries[4].example = "10.107";
  
    queries[5].description = "Distância média percorrida, numa determinada cidade.";
    queries[5].arguments = "<city> <data A> <data B> - Nome da cidade e datas entre as quais a query atua.";
    queries[5].output = "distancia_media";
    queries[5].example = "9.667";
    
    queries[6].description = "Top N condutores numa determinada cidade.";
    queries[6].arguments = "<N> <city> - N condutores a ser listados e nome da cidade.";
    queries[6].output = "id;nome;avaliacao_media";
    queries[6].example = "000000001488;Rita Correia;4.250";

    queries[7].description = "Lista todas as viagens nas quais os utilizadores e o condutor são do género passado como parâmetro e têm perfis com X ou mais anos.";
    queries[7].arguments = "<gender> <X> - Gênero dos utilizadores e condutor e anos mínimos dos seus perfis.";
    queries[7].output = "id_condutor;nome_condutor;username_utilizador;nome_utilizador";
    queries[7].example = "000000009452;Ricardo Figueiredo;WiPinheiro;Wilson de Pinheiro";
    
    queries[8].description = "Lista as viagens nas quais o passageiro deu gorjeta, no intervalo de tempo (data A, data B).";
    queries[8].arguments = "<data A> <data B> - Datas entre as quais a query atua.";
    queries[8].output = "id_viagem;data_viagem;distancia;cidade;valor_gorjeta";
    queries[8].example = "000000295454;01/01/2021;13;Faro;3.000";

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ride.h"

#include <glib.h>
#include "../include/utils.h"
#include "../include/driver_stats.h"
#include "../include/user_stats.h"
#include "../include/city_stats.h"
#include "../include/validation.h"
#include "../include/query5_stats.h"
#include "../include/query6_stats.h"
#include "../include/query7_stats.h"
#include "../include/query8_stats.h"
#include "../include/query9_stats.h"
#include "../include/stats.h"

/* Struct RIDE
 * Responsável por guardar os dados de uma viagem.
 */
struct ride
{
    int id;
    char *date;
    int driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    double tip;
};

// FUNÇÕES GET

char *get_ride_id(RIDE *r)
{
    char *id_str = id_to_string(r->id);
    return id_str;
}

int get_ride_id_int(RIDE *r)
{
    return r->id;
}

char *get_ride_date(RIDE *r)
{
    return strdup(r->date);
}

char *get_ride_driver(RIDE *r)
{
    char* driver_str = id_to_string(r->driver);
    return driver_str;
}

int get_ride_driver_int(RIDE *r)
{
    return r->driver;
}

char *get_ride_user(RIDE *r)
{
    return strdup(r->user);
}

char *get_ride_city(RIDE *r)
{
    return strdup(r->city);
}

int get_ride_distance(RIDE *r)
{
    return r->distance;
}

int get_ride_score_user(RIDE *r)
{
    return r->score_user;
}

int get_ride_score_driver(RIDE *r)
{
    return r->score_driver;
}

double get_ride_tip(RIDE *r)
{
    return r->tip;
}

// FUNÇÕES CREATE / DESTROY

/* Função `create_ride()`
 * Responsável por inicializar uma struct RIDE com todas as informações de uma viagem,
 * contidas numa linha do ficheiro rides.csv.
 */
RIDE *create_ride(char *line, int *v)
{
    RIDE *r = malloc(sizeof(RIDE));

    r->id = atoi(strsep(&line, ";"));
    r->date = strdup(strsep(&line, ";"));
    r->driver = atoi(strsep(&line, ";"));
    r->user = strdup(strsep(&line, ";"));
    r->city = strdup(strsep(&line, ";"));
    char *d = strsep(&line, ";");
    char *su = strsep(&line, ";");
    char *sd = strsep(&line, ";");
    char *t  = strsep(&line, ";");
    r->distance = atoi(d);
    r->score_user = atoi(su);
    r->score_driver = atoi(sd);
    r->tip = atof(t);

    // Validação

    if (!validate_length_int(r->id)) // Validação do tamanho dos campos
        v[0] = 0;
    else if (!validate_length(r->date)) // Validação do tamanho dos campos
        v[0] = 0;
    else if (!validate_date(r->date)) // Validação de datas
        v[0] = 0;
    else if (!validate_length_int(r->driver)) // Validação do tamanho dos campos
        v[0] = 0;
    else if (!validate_length(r->user)) // Validação do tamanho dos campos
        v[0] = 0;
    else if (!validate_length(r->city)) // Validação do tamanho dos campos
        v[0] = 0;
    else if (!validate_length_int(r->distance)) // Validação do tamanho dos campos
        v[0] = 0;
    else if (!validate_distance(d)) // Validação da distância
        v[0] = 0;
    else if (!validate_length_int(r->score_user)) // Validação do tamanho dos campos
        v[0] = 0;
    else if (!validate_score(su)) // Validação dos scores
        v[0] = 0;
    else if (!validate_length_int(r->score_driver)) // Validação do tamanho dos campos
        v[0] = 0;
    else if (!validate_score(sd)) // Validação dos scores
        v[0] = 0;
    else if (!validate_length(t)) // Validação do tamanho dos campos
        v[0] = 0;
    else if (!validate_number(t)) // Validação da tip
        v[0] = 0;
    
    return r;
}

/* Função `destroy_ride()`
 * Responsável por libertar a memória alocada em `create_ride()` para todos os dados que são inicializados usando
 * a função `strdup()`, que efetua um malloc. Liberta também a memória alocada para a struct em si (`free(r)`).
 */
void destroy_ride(void *v)
{
    RIDE *r = v;

    free(r->date);
    free(r->user);
    free(r->city);
    free(r);
}

// PARSING

/* Função `read_rides()`
 * Responsável por fazer o parsing do ficheiro rides.csv. Para cada linha do ficheiro, cria uma struct RIDE
 * com os dados da linha e adiciona-a à hash table `rides`. No fim da execução, liberta a memória alocada e retorna
 * a hash table criada, isto é, um apontador para mesma.
 *
 * Usada também para inicializar as funções `create_driver_stat()` e `create_user_stat()` de criação das hash tables de
 * estatísticas para os users e para os drivers, em cada linha.
 */
GHashTable *read_rides(char *dataset, STATS *stats, GHashTable *drivers, GHashTable *users)
{
    char *path = get_dataset_path(dataset, "rides");

    FILE *file = fopen(path, "r");
    // "../Dataset_Fase1/rides.csv"

    char *line = NULL;
    size_t len = 0;

    GHashTable *rides = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, destroy_ride);

    if (getline(&line, &len, file)) // Ignora a primeira linha do ficheiro (cabeçalho)
    {
    } // Para evitar warnings de unused return value (if)

    int v[1]; // Apontador para guardar o resultado da validação
    while (getline(&line, &len, file) != -1)
    {
        // PARSING DE DADOS

        v[0] = 1; // Reset do resultado da validação

        RIDE *ride = create_ride(line, v);

        if (v[0])
        {
            g_hash_table_insert(rides, &(ride->id), ride);

            // CRIAÇÃO DE ESTATÍSTICAS

            create_driver_stat(ride, get_driver_stats(stats), drivers);
            create_user_stat(ride, get_user_stats(stats), drivers, users);
            create_city_stat(ride, get_city_stats(stats), drivers);
            create_bydate_stat(ride, get_bydate_stats(stats), drivers);
            create_bycitydate_stat(ride, get_bycitydate_stats(stats));
            create_query7_stat(ride, get_query7_stats_hash(stats), drivers);
            create_query8_stats(ride, get_query8_stats_hash(stats), drivers, users);
        }
        else
            destroy_ride(ride);
    }

    fclose(file);
    free(line);
    free(path);

    return rides;
}

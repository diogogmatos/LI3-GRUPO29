#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ride.h"

#include <glib.h>
#include "../include/utils.h"
#include "../include/catalog.h"
#include "../include/driver_stats.h"
#include "../include/user_stats.h"
#include "../include/city_stats.h"

/* Struct RIDE
 * Responsável por guardar os dados de uma viagem.
 */
struct ride
{
    char *id;
    char *date;
    char *driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    double tip;
    char *comment;
};

// FUNÇÕES GET

char *get_ride_id(RIDE *r)
{
    return strdup(r->id);
}

char *get_ride_date(RIDE *r)
{
    return strdup(r->date);
}

char *get_ride_driver(RIDE *r)
{
    return strdup(r->driver);
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

char *get_ride_comment(RIDE *r)
{
    return strdup(r->comment);
}

// FUNÇÕES CREATE / DESTROY

/* Função `create_ride()`
 * Responsável por inicializar uma struct RIDE com todas as informações de uma viagem,
 * contidas numa linha do ficheiro rides.csv.
 */
RIDE *create_ride(char *line)
{
    RIDE *r = malloc(sizeof(RIDE));

    r->id = strdup(strsep(&line, ";"));
    r->date = strdup(strsep(&line, ";"));
    r->driver = strdup(strsep(&line, ";"));
    r->user = strdup(strsep(&line, ";"));
    r->city = strdup(strsep(&line, ";"));
    r->distance = atoi(strsep(&line, ";"));
    r->score_user = atoi(strsep(&line, ";"));
    r->score_driver = atoi(strsep(&line, ";"));
    r->tip = atof(strsep(&line, ";"));
    r->comment = strdup(strsep(&line, "\n")); // o último caracter da linha é um '\n' e não um ';'

    return r;
}

/* Função `destroy_ride()`
 * Responsável por libertar a memória alocada em `create_ride()` para todos os dados que são inicializados usando
 * a função `strdup()`, que efetua um malloc. Liberta também a memória alocada para a struct em si (`free(r)`).
 */
void destroy_ride(void *v)
{
    RIDE *r = v;

    free(r->id);
    free(r->date);
    free(r->driver);
    free(r->user);
    free(r->city);
    free(r->comment);
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
GHashTable *read_rides(char *dataset, GHashTable *user_stats, GHashTable *driver_stats, GHashTable *city_stats, GHashTable *drivers, GHashTable *users)
{
    char *path = get_dataset_path(dataset, "rides");

    FILE *file = fopen(path, "r");
    // "../Dataset_Fase1/rides.csv"

    char *line = NULL;
    size_t len = 0;

    GHashTable *rides = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_ride);

    getline(&line, &len, file);

    while (getline(&line, &len, file) != -1)
    {
        // PARSING DE DADOS

        RIDE *ride = create_ride(line);
        g_hash_table_insert(rides, ride->id, ride);

        // CRIAÇÃO DE ESTATÍSTICAS

        create_driver_stat(ride, driver_stats, drivers);
        create_user_stat(ride, user_stats, drivers, users);
        create_city_stat(ride, city_stats, drivers);
    }

    fclose(file);
    free(line);
    free(path);

    return rides;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/driver.h"

#include <glib.h>
#include "../include/utils.h"
#include "../include/validation.h"

/* Struct DRIVER
 * Responsável por guardar os dados de um condutor.
 */
struct driver
{
    int id;
    char *name;
    char *birth_day;
    char *gender;
    char *car_class;
    char *license_plate;
    char *city;
    char *account_creation;
    char *account_status;
};

// FUNÇÕES GET

char *get_driver_name(DRIVER *d)
{
    return strdup(d->name);
}

char *get_driver_birth_day(DRIVER *d)
{
    return strdup(d->birth_day);
}

char *get_driver_gender(DRIVER *d)
{
    return strdup(d->gender);
}

char *get_driver_car_class(DRIVER *d)
{
    return strdup(d->car_class);
}

char *get_driver_license_plate(DRIVER *d)
{
    return strdup(d->license_plate);
}

char *get_driver_city(DRIVER *d)
{
    return strdup(d->city);
}

char *get_driver_account_creation(DRIVER *d)
{
    return strdup(d->account_creation);
}

char *get_driver_account_status(DRIVER *d)
{
    return strdup(d->account_status);
}

// FUNÇÕES CREATE / DESTROY

/* Função `create_driver()`
 * Responsável por inicializar uma struct DRIVER com todas as informações de um condutor,
 * contidas numa linha do ficheiro drivers.csv.
 */
DRIVER *create_driver(char *line, int *v)
{
    DRIVER *d = malloc(sizeof(DRIVER));

    d->id = atoi(strsep(&line, ";"));
    d->name = strdup(strsep(&line, ";"));
    d->birth_day = strdup(strsep(&line, ";"));
    d->gender = strdup(strsep(&line, ";"));
    d->car_class = strdup(strsep(&line, ";"));
    d->license_plate = strdup(strsep(&line, ";"));
    d->city = strdup(strsep(&line, ";"));
    d->account_creation = strdup(strsep(&line, ";"));
    d->account_status = strdup(strsep(&line, "\n")); // o último caracter da linha é um '\n' e não um ';'

    // Validação

    // Validação do tamanho dos campos (não podem ser vazios)
    if (!validate_length_int(d->id))
        v[0] = 0;
    else if (!validate_length(d->name))
        v[0] = 0;
    else if (!validate_length(d->gender))
        v[0] = 0;
    else if (!validate_length(d->license_plate))
        v[0] = 0;
    else if (!validate_length(d->city))
        v[0] = 0;
    // Validação de datas
    else if (!validate_date(d->birth_day))
        v[0] = 0;
    else if (!validate_date(d->account_creation))
        v[0] = 0;

    return d;
}

/* Função `destroy_driver()`
 * Responsável por libertar a memória alocada em `create_driver()` para todos os dados que são inicializados usando
 * a função `strdup()`, que efetua um malloc. Liberta também a memória alocada para a struct em si (`free(d)`).
 */
void destroy_driver(void *v)
{
    DRIVER *d = v;

    free(d->name);
    free(d->birth_day);
    free(d->gender);
    free(d->car_class);
    free(d->license_plate);
    free(d->city);
    free(d->account_creation);
    free(d->account_status);
    free(d);
}

// PARSING

/* Função `read_drivers()`
 * Responsável por fazer o parsing do ficheiro drivers.csv. Para cada linha do ficheiro, cria uma struct DRIVER
 * com os dados da linha e adiciona-a à hash table `drivers`. No fim da execução, liberta a memória alocada e retorna
 * a hash table criada, isto é, um apontador para mesma.
 */
GHashTable *read_drivers(char *dataset)
{
    char *path = get_dataset_path(dataset, "drivers");

    FILE *file = fopen(path, "r");
    // "../Dataset_Fase1/drivers.csv"

    char *line = NULL;
    size_t len = 0;

    GHashTable *drivers = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, destroy_driver);

    if (getline(&line, &len, file)) // Ignora a primeira linha do ficheiro (cabeçalho)
    {
    } // Para evitar warnings de unused return value (if)

    int v[1]; // Apontador para guardar o resultado da validação
    while (getline(&line, &len, file) != -1)
    {
        v[0] = 1; // Reset do resultado da validação

        DRIVER *driver = create_driver(line, v);

        if (v[0])
            g_hash_table_insert(drivers, &(driver->id), driver);
        else
            destroy_driver(driver);
    }

    fclose(file);
    free(line);
    free(path);

    return drivers;
}

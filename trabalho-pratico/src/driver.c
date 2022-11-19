#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/driver.h"

/* Função `create_driver()`
 * Responsável por inicializar uma struct DRIVER com todas as informações de um condutor,
 * contidas numa linha do ficheiro drivers.csv.
 */
DRIVER *create_driver(char *line)
{
    DRIVER *d = malloc(sizeof(DRIVER));

    d->id = strdup(strsep(&line, ";"));
    d->name = strdup(strsep(&line, ";"));
    d->birth_day = strdup(strsep(&line, ";"));
    d->gender = strdup(strsep(&line, ";"));
    d->car_class = strdup(strsep(&line, ";"));
    d->license_plate = strdup(strsep(&line, ";"));
    d->city = strdup(strsep(&line, ";"));
    d->account_creation = strdup(strsep(&line, ";"));
    d->account_status = strdup(strsep(&line, "\n")); // o último caracter da linha é um '\n' e não um ';'

    return d;
}

/* Função `destroy_driver()`
 * Responsável por libertar a memória alocada em `create_driver()` para todos os dados que são inicializados usando
 * a função `strdup()`, que efetua um malloc. Liberta também a memória alocada para a struct em si (`free(d)`).
 */
void destroy_driver(void *v)
{
    DRIVER *d = v;

    free(d->id);
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

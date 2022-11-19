#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ride.h"

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

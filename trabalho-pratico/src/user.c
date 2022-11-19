#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"

/* Função `create_user()`
 * Responsável por inicializar uma struct USER com todas as informações de um utilizador,
 * contidas numa linha do ficheiro users.csv.
 */
USER *create_user(char *line)
{
    USER *u = malloc(sizeof(USER));

    u->username = strdup(strsep(&line, ";"));
    u->name = strdup(strsep(&line, ";"));
    u->gender = strdup(strsep(&line, ";"));
    u->birth_date = strdup(strsep(&line, ";"));
    u->account_creation = strdup(strsep(&line, ";"));
    u->pay_method = strdup(strsep(&line, ";"));
    u->account_status = strdup(strsep(&line, "\n")); // o último caracter da linha é um '\n' e não um ';'

    return u;
}

/* Função `destroy_user()`
 * Responsável por libertar a memória alocada em `create_user()` para todos os dados que são inicializados usando
 * a função `strdup()`, que efetua um malloc. Liberta também a memória alocada para a struct em si (`free(u)`).
 */
void destroy_user(void *v)
{
    USER *u = v;

    free(u->username);
    free(u->name);
    free(u->gender);
    free(u->birth_date);
    free(u->account_creation);
    free(u->pay_method);
    free(u->account_status);
    free(u);
}

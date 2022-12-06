#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"

#include <glib.h>
#include "../include/utils.h"

/* Struct USER
 * Responsável por guardar os dados de um utilizador.
 */
struct user
{
    char *username;
    char *name;
    char *gender;
    char *birth_date;
    char *account_creation;
    char *pay_method;
    char *account_status;
};

// FUNÇÕES GET

char *get_user_username(USER *u)
{
    return strdup(u->username);
}

char *get_user_name(USER *u)
{
    return strdup(u->name);
}

char *get_user_gender(USER *u)
{
    return strdup(u->gender);
}

char *get_user_birth_date(USER *u)
{
    return strdup(u->birth_date);
}

char *get_user_account_creation(USER *u)
{
    return strdup(u->account_creation);
}

char *get_user_pay_method(USER *u)
{
    return strdup(u->pay_method);
}

char *get_user_account_status(USER *u)
{
    return strdup(u->account_status);
}

// FUNÇÕES CREATE / DESTROY

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

// PARSING

/* Função `read_users()`
 * Responsável por fazer o parsing do ficheiro users.csv. Para cada linha do ficheiro, cria uma struct USER
 * com os dados da linha e adiciona-a à hash table `users`. No fim da execução, liberta a memória alocada e retorna
 * a hash table criada, isto é, um apontador para mesma.
 */
GHashTable *read_users(char *dataset)
{
    char *path = get_dataset_path(dataset, "users");

    FILE *file = fopen(path, "r");
    // "../Dataset_Fase1/users.csv"

    char *line = NULL;
    size_t len = 0;

    GHashTable *users = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_user);

    getline(&line, &len, file);

    while (getline(&line, &len, file) != -1)
    {
        USER *user = create_user(line);
        g_hash_table_insert(users, user->username, user);
    }

    fclose(file);
    free(line);
    free(path);

    return users;
}

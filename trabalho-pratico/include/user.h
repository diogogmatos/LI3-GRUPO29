#ifndef user_h
#define user_h

/* Struct USER
 * Responsável por guardar os dados de um utilizador.
 */
typedef struct user
{
    char *username;
    char *name;
    char *gender;
    char *birth_date;
    char *account_creation;
    char *pay_method;
    char *account_status;
} USER;

USER *create_user(char *line);
void destroy_user(void *v);

#endif

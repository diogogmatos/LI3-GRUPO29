#ifndef user_h
#define user_h

#include <glib.h>

typedef struct user USER;

// FUNÇÕES GET

char *get_user_username(USER *u);
char *get_user_name(USER *u);
char *get_user_gender(USER *u);
char *get_user_birth_date(USER *u);
char *get_user_account_creation(USER *u);
char *get_user_pay_method(USER *u);
char *get_user_account_status(USER *u);

// FUNÇÕES CREATE / DESTROY

USER *create_user(char *line);
void destroy_user(void *v);

// PARSING

GHashTable *read_users(char *dataset);

#endif

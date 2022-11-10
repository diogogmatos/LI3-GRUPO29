#ifndef user_h
#define user_h

typedef struct user
{
    char *username;
    char *name;
    char gender;
    char *date;
    char *account_creation;
    char *pay_method;
    char *account_status;
} USER;

USER *create_user(char *line);

#endif

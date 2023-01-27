#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/validation.h"

int validate_length(char *str)
{
    if (str[0] == '\0')
        return 0;

    return 1;
}

int validate_length_int(int n)
{
    if (n == 0)
        return 0;

    return 1;
}

int validate_date(char *date)
{
    // Verifica se a data tem tamanho suficiente para ser válida
    if (strlen(date) < 10)
        return 0;

    int i;

    // Verifica se os primeiros dois caracteres são números (dia)
    for (i = 0; i < 2; i++)
        if (!isdigit(date[i]))
            return 0;

    // Verifica se o terceiro caracter (i=2) é um '/'
    if (date[i] != '/')
        return 0;

    // Verifica se os caracteres 3 a 4 são números (mês)
    for (i++; i < 5; i++)
        if (!isdigit(date[i]))
            return 0;

    // Verifica se o caracter 5 é um '/'
    if (date[i] != '/')
        return 0;

    // Verifica se os caracteres 6 a 9 são números (ano)
    for (i++; i < 10; i++)
        if (!isdigit(date[i]))
            return 0;

    // -> Se chegou aqui, o formato da data é válido

    int day, month, year;
    sscanf(date, "%d/%d/%d", &day, &month, &year);

    // Verifica se o dia está entre 1 e 31
    if (day < 1 || day > 31)
        return 0;

    // Verifica se o mês está entre 1 e 12
    if (month < 1 || month > 12)
        return 0;

    // -> Se chegou aqui, a data é válida
    return 1;
}

void to_lower_case(char *s)
{
    int i;

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] += 32;
        }
    }
}

int validate_car_class(char *car_class)
{
    to_lower_case(car_class);

    if (!strcmp(car_class, "basic"))
        return 1;
    if (!strcmp(car_class, "green"))
        return 1;
    if (!strcmp(car_class, "premium"))
        return 1;

    return 0;
}

int validate_account_status(char *account_status)
{
    to_lower_case(account_status);

    if (!strcmp(account_status, "active"))
        return 1;
    if (!strcmp(account_status, "inactive"))
        return 1;

    return 0;
}

int validate_int(char *value)
{
    int i;
    for (i = 0; value[i] != '\0'; i++)
    {
        if (!isdigit(value[i]))
            return 0;
    }
    return 1;
}

int validate_distance(char *distance)
{
    if(!validate_int(distance)) // verifica se é um número inteiro
        return 0;

    int d = atoi(distance);
    if (!(d > 0)) // verifica se é um número positivo maior que 0
        return 0;

    return 1;
}

int validate_score(char *score)
{
    if(!validate_int(score)) // verifica se é um número inteiro
        return 0;

    int d = atoi(score);
    if (!(d >= 0)) // verifica se é um número positivo maior ou igual 0
        return 0;

    return 1;
}

// Verifica se uma string é um número inteiro ou décimal
int validate_digits(char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i]))
            if (s[i] != '.')
                return 0;
    }

    return 1;
}

// Verifica se uma string é um número inteiro ou décimal superior ou igual a 0
int validate_number(char *value)
{
    if (!validate_digits(value))
        return 0;

    // -> verifica se value é um número maior ou igual a 0
    if (!(atof(value) >= 0))
        return 0;

    // -> Se chegou até aqui, value é válido
    return 1;
}

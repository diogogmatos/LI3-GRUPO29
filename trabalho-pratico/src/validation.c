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

    for (i = 0; s[i]!='\0'; i++) {
      if(s[i] >= 'A' && s[i] <= 'Z') {
         s[i] += 32;
        }
    }
}

int validate_car_class(char *car_class)
{
    to_lower_case(car_class);

    if (strcmp(car_class, "basic"))
        return 1;
    if (strcmp(car_class, "green"))
        return 1;
    if (strcmp(car_class, "premium"))
        return 1;

    return 0;
}

int validate_account_status(char *account_status)
{
    to_lower_case(account_status);

    if (strcmp(account_status, "active"))
        return 1;
    if (strcmp(account_status, "inactive"))
        return 1;

    return 0;
}

int validate_distance(int distance)
{
    if (distance > 0)
        return 1;

    return 0;
}

// Verifica se uma string é um número inteiro ou décimal
int validate_digits(char *s)
{
    char *t = s;

    while (*t) {
        if ((isdigit(*t) == 0))
        {
          if (*t != '.') return 0;
        }
        t++;
    }

    return 1;
}

// Verifica se uma string é um número inteiro ou décimal superior ou igual a 0
int validate_number(char *tip)
{
    if (validate_digits(tip) == 0) return 0;

    // -> verifica se a tip é um número maior ou igual a 0
    if ((atof(tip) < 0))
        return 0;

    // -> Se chegou até aqui, a tip é válida
    return 1;
}
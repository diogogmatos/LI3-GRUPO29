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

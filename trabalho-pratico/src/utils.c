#include "../include/driver.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODAY "09/10/2022" // Data usada para calcular a idade dos users

// CLASSES

/* Função `get_price()`
 * Responsável por obter o preço da tarifa mínima de uma viagem de acordo com a classe do veículo do condutor, dado um
 * condutor `d`.
 */
double get_price(DRIVER *d)
{
    double r;
    char *car_class = get_driver_car_class(d);

    switch (car_class[0])
    {
    case 'b': // class basic
        r = 3.25;
        free(car_class);
        return r;

    case 'g': // class green
        r = 4.00;
        free(car_class);
        return r;

    case 'p': // class premium
        r = 5.20;
        free(car_class);
        return r;
    default:
        free(car_class);
        return 0;
    }
}

/* Função `get_tax()`
 * Responsável por obter a taxa/custo por kilómetro de uma viagem de acordo com a classe do veículo do condutor, dado um
 * condutor `d`.
 */
double get_tax(DRIVER *d)
{
    double r;
    char *car_class = get_driver_car_class(d);

    switch (car_class[0])
    {
    case 'b': // class basic
        r = 0.62;
        free(car_class);
        return r;

    case 'g': // class green
        r = 0.79;
        free(car_class);
        return r;

    case 'p': // class premium
        r = 0.94;
        free(car_class);
        return r;
    default:
        free(car_class);
        return 0;
    }
}

// DATAS

/* Função `convert_date()`
 * Responsável por converter uma data no formato DD/MM/YYYY para um inteiro que representa o número total de
 * dias que essa data contém. Usada em `get_age()` para calcular idades e nas funções de estatísticas para comparar datas.
 */
int convert_date(char *date)
{
    int dia, mes, ano;

    sscanf(date, "%d/%d/%d", &dia, &mes, &ano);

    int r = ano * 365 + mes * 31 + dia;

    return r;
}

/* Função `get_age()`
 * Responsável por calcular a idade de um utilizador ou condutor, dada a sua data de nascimento (`date`).
 */
int get_age(char *date)
{
    int t = convert_date(TODAY);
    int d = convert_date(date);

    int r = (t - d) / 365;

    return r;
}

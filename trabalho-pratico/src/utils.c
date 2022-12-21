#include "../include/driver.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TODAY "09/10/2022" // Data usada para calcular a idade dos users

// PATHS

/* Função `get_results_path()`
 * Responsável por obter o caminho para o ficheiro de resultados de um comando `i`.
 */
char *get_results_path(int i)
{
    char *path = malloc(sizeof(char) * 32);
    sprintf(path, "Resultados/command%d_output.txt", i);

    return path;
}

/* Função `get_dataset_path()`
 * Responsável por obter o caminho para o ficheiro de dados do tipo `type`.
 */
char *get_dataset_path(char *dataset, char *type)
{
    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "%s/%s.csv", dataset, type);

    return path;
}

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
 * dias entre essa data e o dia de "hoje". Usada em `get_age()` para calcular idades e nas funções de estatísticas para comparar datas.
 */
int convert_date(char *date)
{
    int dia1, mes1, ano1, dia2, mes2, ano2;

    sscanf(TODAY, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(date, "%d/%d/%d", &dia2, &mes2, &ano2);

    struct tm date1 = {0}, date2 = {0};
    date1.tm_year = ano1 - 1900;
    date1.tm_mon = mes1 - 1;
    date1.tm_mday = dia1;
    date2.tm_year = ano2 - 1900;
    date2.tm_mon = mes2 - 1;
    date2.tm_mday = dia2;

    time_t t1 = mktime(&date1);
    time_t t2 = mktime(&date2);

    double diff = difftime (t1, t2);

    int r = diff / (60 * 60 * 24);

    return r;
}

/* Função `get_age()`
 * Responsável por calcular a idade de um utilizador ou condutor, dada a sua data de nascimento (`date`).
 */
int get_age(char *date)
{
    int d = convert_date(date);

    int r = d / 365;

    return r;
}

int compare_dates(char *date1, char *date2)
{
    int dia1, mes1, ano1, dia2, mes2, ano2, r;

    sscanf(date1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(date2, "%d/%d/%d", &dia2, &mes2, &ano2);

    if ((ano1 > ano2) || (ano1 == ano2 && mes1 > mes2) || (ano1 == ano2 && mes1 == mes2 && dia1 > dia2))
        r = 1;
    else if (ano1 == ano2 && mes1 == mes2 && dia1 == dia2)
        r = 0;
    else
        r = -1;

    return r;
}
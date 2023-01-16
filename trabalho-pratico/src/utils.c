#include "../include/driver.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

#define TODAY "09/10/2022" // Data usada para calcular a idade dos users

// PATHS

/* Função `get_results_path()`
 * Responsável por obter o caminho para o ficheiro de resultados de um comando `i`.
 */
char *get_results_path(int i)
{
    char *path = malloc(sizeof(char) * 50);
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

// is leap year in Gregorian
long IsLeapG(long yr)
{
    if (((((yr % 400) == 0) || ((yr % 100) != 0)) && ((yr % 4) == 0)))
        return (1);
    else
        return (0);
}

// Day of the Year
long rbdug(long d, long m, long y)
{
    long a, r[13];

    r[1] = 0;
    r[2] = 31;
    r[3] = 59;
    r[4] = 90;
    r[5] = 120;
    r[6] = 151;
    r[7] = 181;
    r[8] = 212;
    r[9] = 243;
    r[10] = 273;
    r[11] = 304;
    r[12] = 334;

    a = r[m] + d;

    if ((IsLeapG(y) == 1) && (m > 2))
        a += 1;
    return (a);
}

long Godn(long yy1, long yy2)
{
    long jj, bb;
    bb = 0;

    for (jj = yy1; jj < yy2; jj++)
    {
        bb += 365;
        if (IsLeapG(jj) == 1)
            bb += 1;
    }

    return (bb);
}

long DatDif(long d1, long m1, long y1, long d2, long m2, long y2)
{
    long suma;
    suma = rbdug(d2, m2, y2) - rbdug(d1, m1, y1);

    if (y1 != y2)
    {
        if (y1 < y2)
            suma += Godn(y1, y2);
        else
            suma -= Godn(y2, y1);
    }

    return (suma);
}

// Returns 1 if the given year is a leap year, 0 otherwise.
int is_leap_year(int year)
{
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    if (year % 4 == 0)
        return 1;
    return 0;
}

// Returns the number of days in the given month (1-based) in the given year.
int days_in_month(int month, int year)
{
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year))
        return 29;
    return days[month];
}

// Increases the given date string by one day.
void increase_date(char *date)
{
    // Parse the year, month, and day from the date string.
    int year, month, day;
    sscanf(date, "%d/%d/%d", &day, &month, &year);

    // Increase the day by one.
    day++;
    if (day > days_in_month(month, year))
    {
        // If the day is now invalid, set it to 1 and increase the month.
        day = 1;
        month++;
        if (month > 12)
        {
            // If the month is now invalid, set it to 1 and increase the year.
            month = 1;
            year++;
        }
    }

    // Update the date string with the incremented date.
    sprintf(date, "%02d/%02d/%04d", day, month, year);
}

void increase_something_date(char *something_date)
{
    char *date = strchr(something_date, '-') + 1;

    increase_date(date);
}

/* Função `convert_date()`
 * Responsável por converter uma data no formato DD/MM/YYYY para um inteiro que representa o número total de
 * dias entre essa data e o dia de "hoje". Usada em `get_age()` para calcular idades e nas funções de estatísticas para comparar datas.
 */
int convert_date(char *date)
{
    long d1, m1, y1, d2, m2, y2;

    sscanf(date, "%ld/%ld/%ld", &d1, &m1, &y1);
    sscanf(TODAY, "%ld/%ld/%ld", &d2, &m2, &y2);

    return DatDif(d1, m1, y1, d2, m2, y2);
}

/* Função `get_age()`
 * Responsável por calcular a idade de um utilizador ou condutor, dada a sua data de nascimento (`date`).
 */
int get_age(char *date)
{
    int d = convert_date(date);

    int r = d / 365.2425;

    return r;
}

int compare_dates(char *date1, char *date2)
{
    int dia1, mes1, ano1, dia2, mes2, ano2;

    sscanf(date1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(date2, "%d/%d/%d", &dia2, &mes2, &ano2);

    if ((ano1 > ano2) || (ano1 == ano2 && mes1 > mes2) || (ano1 == ano2 && mes1 == mes2 && dia1 > dia2))
        return 1;

    if (ano1 == ano2 && mes1 == mes2 && dia1 == dia2)
        return 0;

    return -1;
}

// OUTROS

void print_time_and_memory()
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    double user_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1000000.0;
    double sys_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1000000.0;
    double total_time = user_time + sys_time;
    printf("\nMemory usage: %ld MB\n", usage.ru_maxrss / 1000);
    int time = total_time;
    if (total_time < 60)
        printf("CPU time: %.3f seconds\n", total_time);
    else
        printf("CPU time: %d minutes and %d seconds (%.3f seconds)\n", time / 60, time % 60, total_time);
}

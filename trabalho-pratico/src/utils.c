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

void display_stats()
{
    // Get the current memory usage
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("\nMemory usage: %ld MiB\n", usage.ru_maxrss / 1024);

    // Get the current CPU time
    clock_t clock_time = clock();
    long clock_time_sec = clock_time / CLOCKS_PER_SEC;
    if (clock_time_sec < 60)
        printf("CPU time: %ld seconds\n", clock_time_sec);
    else
        printf("CPU time: %ld minutes and %ld seconds (%ld seconds)\n", clock_time_sec / 60, clock_time_sec % 60, clock_time_sec);
}

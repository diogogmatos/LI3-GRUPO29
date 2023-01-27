#ifndef utils_h
#define utils_h

#include "driver.h"
#include <time.h>
#include <glib.h>

char *get_results_path(int i);
char *get_dataset_path(char *dataset, char *type);
double get_price(DRIVER *d);
double get_tax(DRIVER *d);
int convert_date(char *date);
int get_age(char *date);
int compare_dates(char *date1, char *date2);
void increase_date(char *date);
void increase_something_date(char *something_date);
char *id_to_string(int id);
void print_time_and_memory();
void print_query_time(clock_t start, clock_t end);
void print_loading_time(clock_t start, clock_t end, char *str);

#endif

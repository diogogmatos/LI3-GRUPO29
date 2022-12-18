#ifndef utils_h
#define utils_h

#include "../include/driver.h"
#include <glib.h>

char *get_results_path(int i);
char *get_dataset_path(char *dataset, char *type);
double get_price(DRIVER *d);
double get_tax(DRIVER *d);
int convert_date(char *date);
int get_age(char *date);
int compare_dates(char *date1, char *date2);

#endif

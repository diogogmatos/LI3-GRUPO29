#ifndef utils_h
#define utils_h

#include "../include/driver.h"
#include <glib.h>

double get_price(DRIVER *d);
double get_tax(DRIVER *d);
int convert_date(char *date);
int get_age(char *date);

#endif

#ifndef driver_h
#define driver_h

#include <glib.h>

typedef struct driver DRIVER;

// FUNÇÕES GET

char *get_driver_name(DRIVER *d);
char *get_driver_birth_day(DRIVER *d);
char *get_driver_gender(DRIVER *d);
char *get_driver_car_class(DRIVER *d);
char *get_driver_license_plate(DRIVER *d);
char *get_driver_city(DRIVER *d);
char *get_driver_account_creation(DRIVER *d);
char *get_driver_account_status(DRIVER *d);

// FUNÇÕES CREATE / DESTROY

DRIVER *create_driver(char *line, int *v);
void destroy_driver(void *v);

// PARSING

GHashTable *read_drivers(char *dataset);

#endif
#ifndef driver_h
#define driver_h

typedef struct driver
{
    char *id;
    char *name;
    char *birth_day;
    char gender;
    char *car_class;
    char *license_plate;
    char *city;
    char *account_creation;
    char *account_status;
} DRIVER;

DRIVER *create_driver(char *line);

#endif
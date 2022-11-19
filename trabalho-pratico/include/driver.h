#ifndef driver_h
#define driver_h

/* Struct DRIVER
 * Responsável por guardar os dados de um condutor.
 */
typedef struct driver
{
    char *id;
    char *name;
    char *birth_day;
    char *gender;
    char *car_class;
    char *license_plate;
    char *city;
    char *account_creation;
    char *account_status;
} DRIVER;

DRIVER *create_driver(char *line);
void destroy_driver(void *v);

#endif
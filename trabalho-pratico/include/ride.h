#ifndef ride_h
#define ride_h

/* Struct RIDE
 * Responsável por guardar os dados de uma viagem.
 */
typedef struct ride
{
    char *id;
    char *date;
    char *driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    double tip;
    char *comment;
} RIDE;

RIDE *create_ride(char *line);
void destroy_ride(void *v);

#endif
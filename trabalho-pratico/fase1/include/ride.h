#ifndef ride_h
#define ride_h

typedef struct ride
{
    int id;
    char *date;
    int driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    float tip;
    char *comment;
} RIDE;

RIDE *create_ride(char *line);

#endif
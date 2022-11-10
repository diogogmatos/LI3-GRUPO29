#ifndef ride_h
#define ride_h

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

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/user.h"
#include "../include/driver.h"
#include "../include/ride.h"
#include "../include/parsing.h"

GHashTable *read_drivers()
{
    FILE *file = fopen("../Dataset_Fase1/drivers.csv", "r");

    char *line = NULL;
    size_t len = 0;

    GHashTable *drivers = g_hash_table_new(g_int_hash, g_int_equal);

    getline(&line, &len, file);

    while (getline(&line, &len, file) != -1)
    {
        DRIVER *driver = create_driver(line);
        g_hash_table_insert(drivers, &driver->id, driver);
    }

    fclose(file);

    return drivers;
}

GHashTable *read_users()
{
    FILE *file = fopen("../Dataset_Fase1/users.csv", "r");

    char *line = NULL;
    size_t len = 0;

    GHashTable *users = g_hash_table_new(g_str_hash, g_str_equal);

    getline(&line, &len, file);

    while (getline(&line, &len, file) != -1)
    {
        USER *user = create_user(line);
        g_hash_table_insert(users, user->username, user);
    }

    fclose(file);

    return users;
}

GHashTable *read_rides()
{
    FILE *file = fopen("../Dataset_Fase1/rides.csv", "r");

    char *line = NULL;
    size_t len = 0;

    GHashTable *rides = g_hash_table_new(g_int_hash, g_int_equal);

    getline(&line, &len, file);

    while (getline(&line, &len, file) != -1)
    {
        RIDE *ride = create_ride(line);
        g_hash_table_insert(rides, &ride->id, ride);
    }

    fclose(file);

    return rides;
}

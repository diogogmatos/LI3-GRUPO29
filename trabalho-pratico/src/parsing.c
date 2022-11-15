#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/user.h"
#include "../include/driver.h"
#include "../include/ride.h"
#include "../include/parsing.h"

GHashTable *read_drivers(char *dataset)
{
    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "%s/drivers.csv", dataset);

    FILE *file = fopen(path, "r");
    // "../Dataset_Fase1/drivers.csv"

    char *line = NULL;
    size_t len = 0;

    GHashTable *drivers = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_driver);

    getline(&line, &len, file);

    while (getline(&line, &len, file) != -1)
    {
        DRIVER *driver = create_driver(line);
        g_hash_table_insert(drivers, driver->id, driver);
    }

    fclose(file);
    free(line);
    free(path);

    return drivers;
}

GHashTable *read_users(char *dataset)
{
    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "%s/users.csv", dataset);

    FILE *file = fopen(path, "r");
    // "../Dataset_Fase1/users.csv"

    char *line = NULL;
    size_t len = 0;

    GHashTable *users = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_user);

    getline(&line, &len, file);

    while (getline(&line, &len, file) != -1)
    {
        USER *user = create_user(line);
        g_hash_table_insert(users, user->username, user);
    }

    fclose(file);
    free(line);
    free(path);

    return users;
}

GHashTable *read_rides(char *dataset)
{
    char *path = malloc(sizeof(char) * 50);
    sprintf(path, "%s/rides.csv", dataset);

    FILE *file = fopen(path, "r");
    // "../Dataset_Fase1/rides.csv"

    char *line = NULL;
    size_t len = 0;

    GHashTable *rides = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroy_ride);

    getline(&line, &len, file);

    while (getline(&line, &len, file) != -1)
    {
        RIDE *ride = create_ride(line);
        g_hash_table_insert(rides, ride->id, ride);
    }

    fclose(file);
    free(line);
    free(path);

    return rides;
}

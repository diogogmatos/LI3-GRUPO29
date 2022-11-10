#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/driver.h"
#include "../include/user.h"
#include "../include/ride.h"
#include "../include/parsing.h"

int main(int argc, char **argv)
{
    GHashTable *rides = read_rides();
    int key = 999999;
    RIDE *ride = g_hash_table_lookup(rides, &key);
    printf("%s", ride->city);
    return 0;
}
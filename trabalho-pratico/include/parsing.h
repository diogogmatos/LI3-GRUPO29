#ifndef parsing_h
#define parsing_h

#include <glib.h>

GHashTable *read_users(char *dataset);
GHashTable *read_drivers(char *dataset);
GHashTable *read_rides(char *dataset);

#endif
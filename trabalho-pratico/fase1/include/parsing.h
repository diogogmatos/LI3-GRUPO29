#ifndef parsing_h
#define parsing_h

#include <glib.h>

GHashTable *read_users();
GHashTable *read_drivers();
GHashTable *read_rides();

#endif
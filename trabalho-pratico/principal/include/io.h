#ifndef io_h
#define io_h

#include <glib.h>
#include "../include/stats.h"

void handle_input(int query, char *input, GHashTable *d, GHashTable *u, GHashTable *r, STATS *s, int i);
void run_queries(char *dataset, char *input);

#endif
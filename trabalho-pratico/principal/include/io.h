#ifndef io_h
#define io_h

#include <glib.h>
#include "../include/catalog.h"

void handle_input(int query, char *input, CATALOG *c, int i);
void run_queries(char *dataset, char *input);

#endif
#ifndef queries_h
#define queries_h

#include <glib.h>
#include "../include/catalog.h"

void query_1(int is_id, char *value, char *path, CATALOG *c);
void query_2(int N, char *path, CATALOG *c);
void query_3(int N, char *path, CATALOG *c);
void invalid_query(char *path);

#endif
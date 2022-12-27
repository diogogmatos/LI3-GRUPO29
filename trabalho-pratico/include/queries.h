#ifndef queries_h
#define queries_h

#include <glib.h>
#include "../include/catalog.h"

void query_1(int is_id, char *value, char *path, CATALOG *c);
void query_2(int N, char *path, CATALOG *c);
void query_3(int N, char *path, CATALOG *c);
void query_4(char *city, char *path, CATALOG *c);
void query_5(char *date_a, char *date_b, char *path, CATALOG *c);
void query_6(char *city, char *date_a, char *date_b, char *path, CATALOG *c);
void query_7(int N, char *city, char *path, CATALOG *c);
void query_8(char *gender, int X, char *path, CATALOG *c);
void invalid_query(char *path);

#endif
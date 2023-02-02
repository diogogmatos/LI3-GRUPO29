#ifndef queries_h
#define queries_h

#include <glib.h>
#include "../include/stats.h"

void query_1(int is_id, char *value, char *path, GHashTable *drivers, GHashTable *users, STATS *s);
void query_2(int N, char *path, STATS *s);
void query_3(int N, char *path, STATS *s);
void query_4(char *city, char *path, STATS *s);
void query_5(char *date_a, char *date_b, char *path, STATS *s);
void query_6(char *city, char *date_a, char *date_b, char *path, STATS *s);
void query_7(int N, char *city, char *path, GHashTable *drivers, STATS *s);
void query_8(char *gender, int X, char *path, GHashTable *drivers, GHashTable *users, GHashTable *rides, STATS *s);
void query_9(char *date_a, char *date_b, char *path, GHashTable *rides);
void invalid_query(char *path);

#endif
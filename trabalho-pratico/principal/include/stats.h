#ifndef stats_h
#define stats_h

typedef struct stats STATS;

GHashTable *get_driver_stats(STATS *s);
GHashTable *get_user_stats(STATS *s);
GHashTable *get_city_stats(STATS *s);
GList *get_query2_stats(STATS *s);
GList *get_query3_stats(STATS *s);
GHashTable *get_bydate_stats(STATS *s);
GHashTable *get_bycitydate_stats(STATS *s);
GHashTable *get_query7_stats_hash(STATS *s);
GList *get_query7_stats(STATS *s);
GHashTable *get_query8_stats_hash(STATS *s);
GList *get_query8_stats(STATS *s);

STATS *create_stats();
void sort_stats(STATS *s);
void destroy_stats(void *v);
#endif

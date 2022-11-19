#ifndef stat_h
#define stat_h

#include "../include/user.h"
#include "../include/driver.h"
#include "../include/catalog.h"
#include <glib.h>

/* Struct STAT
 * Usada nas funções de estatísticas para guardar os dados necessários para a sua execução:
 * Dados de utilizadores, condutores e dados auxiliares.
 */
typedef struct stat
{
	int age;	  // q1
	double money; // q1

	double score;	   // q2
	char *driver_name; // q2

	char *user_name;	// q3
	int total_distance; // q3

	char *id;				// q1, q2
	double avg_score;		// q1, q2
	int trips;				// q1, q2

	char *username;			// q1, q3

	char *most_recent_trip; // q2, q3
	GHashTable *ht;			// q2, q3

	CATALOG *c;				// q1, q2, q3
} STAT;

STAT *user_stat(USER *u, CATALOG *c);
STAT *driver_stat(DRIVER *d, CATALOG *c);
GHashTable *avg_score_stats(CATALOG *c);
GHashTable *tot_dist_stats(CATALOG *c);

#endif

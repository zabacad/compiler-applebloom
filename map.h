/*
 *  map.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef MAP_H
#define MAP_H




#include "stdlib.h"
#include "string.h"




/* Constant settings. */
#define MAP_SUBS 32
#define MAP_ENTRIES 32




/* Data types. */
typedef struct map map_t;

struct map
{
	struct map_sub **subs;
};

struct map_sub
{
	struct map_entry **entries;
};

struct map_entry
{
	char *key;
	void *data;
	struct map_entry *next;
};




/* Prototypes. */
map_t *map_create();
void map_destroy(map_t *map);
void map_set(map_t *map, char *key, void *data, size_t data_len);
void *map_get(map_t *map, char *key);
void map_remove(map_t *map, char *key);




#endif /* MAP_H */

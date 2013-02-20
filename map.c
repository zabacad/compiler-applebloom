/*
 *  map.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "map.h"




/*
 *  Create and return a map.
 */
map_t *map_create()
{
	map_t *map;
	int i;


	map = malloc(sizeof(struct map));
	for (i = 0; i < MAP_SUBS; i++)
		map->subs[i] = NULL;

	return map;
}


/*
 *  Destroy `map' and its data.
 */
void map_destroy(map_t *map)
{
}


/*
 *  Set the `data' at `key', removing the old data.
 */
void map_set(map_t *map, char *key, void *data, size_t data_len)
{
	int hash;
	int hash_sub;

	int i;

	int key_len;
	struct map_entry *prev;
	struct map_entry *entry;


	/* Calculate hash based on `key'. */
	hash = map_hash(key);
	hash_sub = map_hash_sub(key);

	/* Create the submap if it does not exist. */
	if (map->subs[hash] == NULL)
	{
		map->subs[hash] = (struct map_sub *)malloc(sizeof(struct map_sub));
		for (i = 0; i < MAP_ENTRIES; i++)
			map->subs[hash]->entries[i] = NULL;
	}

	/* If the key is in use, change the data. */
	while ((entry = map->subs[hash]->entries[hash_sub]) != NULL)
	{
		if (strcmp(entry->key, key) == 0)
		{
			free(entry->data);
			entry->data = malloc(data_len);
			memcpy(entry->data, data, data_len);
			return;
		}
	}

	/* If the key is not in use, create a new entry */
	entry = (struct map_entry *)malloc(sizeof(struct map_entry));
	key_len = strlen(key) + 1;
	entry->key = (char *)malloc(key_len * sizeof(char));
	memcpy(entry->key, key, key_len);
	entry->data = malloc(data_len);
	memcpy(entry->data, data, data_len);

	/* Link the (possibly empty) chain after the entry. */
	entry->next = map->subs[hash]->entries[hash_sub];
	map->subs[hash]->entries[hash_sub] = entry;
}


/*
 *  Get the data at `key'.
 */
void *map_get(map_t *map, char *key)
{
	int hash;
	int hash_sub;

	struct map_entry *entry;


	/* Calculate hash based on `key'. */
	hash = map_hash(key);
	hash_sub = map_hash_sub(key);

	/* Find the first entry with matching key on the chain. NULL if none. */
	entry = map->subs[hash]->entries[hash_sub];
	while (entry != NULL)
	{
		if (strcmp(entry->key, key) == 0)
			break;
		entry = entry->next;
	}

	return entry;
}


/*
 *  Remove the entry at `key'.
 */
void map_remove(map_t *map, char *key)
{
}


/*
 *  Generate hash.
 */
static int map_hash(char *key)
{
	return (int)(key[0] && (MAP_SUBS - 1));
}
static int map_hash_sub(char *key)
{
	int hash_sub = 0;


	if (key[0] != '\0')
		hash_sub = (int)(key[1] && (MAP_ENTRIES - 1));

	return hash_sub;
}

/*
 *  tree.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef TREE_H
#define TREE_H




#include "string.h"




typedef struct tree tree_t;
typedef struct tree_node tree_node_t;

struct tree
{
	tree_node_t *root;
};

struct tree_node
{
	void *data;
	tree_node_t *children;
	int num_children;
};




tree_t *tree_create(void *data, size_t data_size);
void tree_destroy(tree_t *tree);
tree_node_t *tree_node_create(void *data, size_t data_size);
void tree_node_destroy(tree_node_t *node);




#endif /* TREE_H */

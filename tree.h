/*
 *  tree.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef TREE_H
#define TREE_H




#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/* Data types. */
typedef struct tree tree_t;
typedef struct tree_node tree_node_t;

struct tree
{
	tree_node_t *root;
};

struct tree_node
{
	void *data;
	tree_node_t **children;
	int num_children;
};




/* Prototypes. */
tree_t *tree_create();
void tree_destroy(tree_t *tree);
void tree_set_root(tree_t *tree, tree_node_t *root);
tree_node_t *tree_get_root(tree_t *tree);

tree_node_t *tree_node_create(void *data, size_t data_size);
void tree_node_destroy(tree_node_t *node);
void tree_node_set_data(tree_node_t *node, void *data, size_t data_size);
void *tree_node_get_data(tree_node_t *node);
void tree_node_add_child(tree_node_t *parent, tree_node_t *child, int index);
void tree_node_remove_child(tree_node_t *parent, int index);
tree_node_t *tree_node_get_child(tree_node_t *parent, int index);




#endif /* TREE_H */

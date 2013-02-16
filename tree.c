/*
 *  tree.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "tree.h"




tree_t *tree_create(void *data, size_t data_size)
{
	tree_t *tree;
	tree_node_t *root;


	tree = (tree_t *)malloc(sizeof(tree_t));

	root = tree_node_create(data, data_size);

	tree->root = root;

	return tree;
}


void tree_destroy(tree_t *tree)
{
	tree_node_destroy(tree->root);
	free(tree);
}


tree_node_t *tree_node_create(void *data, size_t data_size)
{
	tree_node_t *node;


	node = (tree_node_t *)malloc(sizeof(tree_node_t));
	node->num_children = 0;
	node->data = malloc(data_size);
	memcpy(node->data, data, data_size);

	return node;
}


void tree_node_destroy(tree_node_t *node)
{
	int child;


	for (child = 0; child < node->num_children; child++)
	{
		tree_node_destroy(&node->children[child]);
	}

	free(node->data);
	free(node);
}

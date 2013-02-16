/*
 *  tree.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "tree.h"




/*
 *  Create and return a tree with a copy of `data' at the root node.
 *  `data_size' bytes of data are copied.
 */
tree_t *tree_create(void *data, size_t data_size)
{
	tree_t *tree;
	tree_node_t *root;


	tree = (tree_t *)malloc(sizeof(tree_t));

	root = tree_node_create(data, data_size);

	tree->root = root;

	return tree;
}


/*
 *  Destroy a tree and all its data.
 */
void tree_destroy(tree_t *tree)
{
	tree_node_destroy(tree->root);
	free(tree);
}


/*
 *  Create and return a tree node with a copy of `data'. `data_size' bytes of
 *  data are copied.
 */
tree_node_t *tree_node_create(void *data, size_t data_size)
{
	tree_node_t *node;


	node = (tree_node_t *)malloc(sizeof(tree_node_t));
	node->num_children = 0;
	node->children = NULL;
	node->data = malloc(data_size);
	memcpy(node->data, data, data_size);

	return node;
}


/*
 *  Destroy a node and its data and its decendants and their data.
 */
void tree_node_destroy(tree_node_t *node)
{
	int child;


	for (child = 0; child < node->num_children; child++)
		tree_node_destroy(node->children[child]);

	free(node->data);
	free(node->children);
	free(node);
}


/*
 *  Copy data into a node.
 */
void tree_node_set_data(tree_node_t *node, void *data, size_t data_size)
{
	/* Destroy old data. */
	free(node->data);

	/* Copy new data. */
	node->data = malloc(data_size);
	memcpy(node->data, data, data_size);
}


/*
 *  Add a `child' node to a tree as the `index' child of `parent'. A negative
 *  `index' appends the child as the last child of parent.
 */
void tree_node_add_child(tree_node_t *parent, tree_node_t *child, int index)
{
	int c;


	if (index < 0)
		index = parent->num_children;

	/* Add space for child reference. */
	parent->num_children++;
	parent->children = (tree_node_t **)realloc(
		parent->children,
		(size_t)(parent->num_children * sizeof(tree_node_t *))
	);

	/* Shift children to make space. */
	for (c = parent->num_children - 1; c > index; c++)
		parent->children[c] = parent->children[c - 1];

	/* Add child. */
	parent->children[index] = child;
}


/*
 *  Remove the `index' child node from a `parent' node. Orphans the child, but
 *  does not destroy any nodes or data.
 */
void tree_node_remove_child(tree_node_t *parent, int index)
{
	int c;


	/* Shift children over into removed child. */
	for (c = index; c < parent->num_children - 1; c++)
		parent->children[c] = parent->children[c + 1];

	/* Free space used by removed child. */
	parent->num_children--;
	parent->children = (tree_node_t **)realloc(
		parent->children,
		(size_t)(parent->num_children * sizeof(tree_node_t *))
	);
}

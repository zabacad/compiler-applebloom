/*
 *  tree.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "tree.h"




/*
 *  Create and return an empty tree.
 */
tree_t *tree_create()
{
	tree_t *tree;


	tree = (tree_t *)malloc(sizeof(tree_t));

	tree->root = NULL;

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
 *  Set the root `node' of a `tree'. Ignores any previous root.
 */
void tree_set_root(tree_t *tree, tree_node_t *node)
{
	tree->root = node;
}


/*
 *  Return the root node of a `tree'. NULL on invalid.
 */
tree_node_t *tree_get_root(tree_t *tree)
{
	if (tree == NULL)
	{
		fprintf(stderr, "Attempted to get root of NULL tree.\n");
		return NULL;
	}

	return tree->root;
}


/*
 *  Create and return a tree node with a copy of `data'. `data_size' bytes of
 *  data are copied. A `data' of NULL or a `data_size' less than one creates a
 *  node with no data.
 */
tree_node_t *tree_node_create(void *data, size_t data_size)
{
	tree_node_t *node;


	node = (tree_node_t *)malloc(sizeof(tree_node_t));

	node->data = NULL;
	node->children = NULL;
	node->num_children = 0;

	if ((data != NULL) && (data_size > 0))
	{
		node->data = malloc(data_size);
		memcpy(node->data, data, data_size);
	}

	return node;
}


/*
 *  Destroy `node' and its data and the node's descendants and their data.
 */
void tree_node_destroy(tree_node_t *node)
{
	int i;


	for (i = 0; i < node->num_children; i++)
		tree_node_destroy(node->children[i]);

	free(node->data);
	free(node->children);
	free(node);
}


/*
 *  Copy `data' into `node'. `data_size' bytes of data are copied. A `data' of
 *  NULL or a `data_size' less than one leaves the `node' with no data.
 */
void tree_node_set_data(tree_node_t *node, void *data, size_t data_size)
{
	if (node == NULL)
	{
		fprintf(stdout, "Attempted to copy data into NULL node.\n");
		return;
	}

	/* Destroy old data. */
	free(node->data);
	node->data = NULL;

	/* Copy new data. */
	if ((data != NULL) && (data_size > 0))
	{
		node->data = malloc(data_size);
		memcpy(node->data, data, data_size);
	}
}


/*
 *  Get the data at `node'.
 */
void *tree_node_get_data(tree_node_t *node)
{
	return node->data;
}


/*
 *  Insert a `child' node as the `index' child of `parent'. A negative `index'
 *  appends the `child' as the last child of `parent'.
 */
void tree_node_add_child(tree_node_t *parent, tree_node_t *child, int index)
{
	int i;


	if (index < 0)
		index = parent->num_children;

	/* Add space for child reference. */
	parent->num_children++;
	parent->children = (tree_node_t **)realloc(parent->children,
		(size_t)(parent->num_children * sizeof(tree_node_t *)));

	/* Shift children to make space. */
	for (i = parent->num_children - 1; i > index; i--)
		parent->children[i] = parent->children[i - 1];

	/* Add child. */
	parent->children[index] = child;
}


/*
 *  Remove the `index' child node from a `parent' node. Orphans the child, but
 *  does not destroy any nodes or data.
 */
void tree_node_remove_child(tree_node_t *parent, int index)
{
	int i;


	/* Shift children over into removed child. */
	for (i = index; i < parent->num_children - 1; i++)
		parent->children[i] = parent->children[i + 1];

	/* Free space used by removed child. */
	parent->num_children--;
	parent->children = (tree_node_t **)realloc(parent->children,
		(size_t)(parent->num_children * sizeof(tree_node_t *)));
}


/*
 *  
 */
int tree_node_get_num_children(tree_node_t *node)
{
	if (node == NULL)
	{
		fprintf(stderr, "Attempted to get number of children of NULL node.\n");
		return 0;
	}

	return node->num_children;
}


/*
 *  Get the `index' child of `parent'. NULL when invalid.
 */
tree_node_t *tree_node_get_child(tree_node_t *parent, int index)
{
	if (parent == NULL)
	{
		fprintf(stdout, "Attempted to get child of NULL node.\n");
		return NULL;
	}

	if (index >= parent->num_children)
	{
		fprintf(stdout, "Attempted to get child out of bounds.\n");
		return NULL;
	}

	return parent->children[index];
}

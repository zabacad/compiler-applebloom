/*
 *  translator.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "translator.h"




/*
 *  
 */
void translator_translate(tree_t *tree)
{
	tree_node_t *root;


	printf("Translating...\n");

	root = tree_get_root(tree);

	translator_postorder(root);

	printf("\n");
}


/*
 *  
 */
void translator_postorder(tree_node_t *node)
{
	int i;
	token_t *token;


	for (i = 0; i < tree_node_get_num_children(node); i++)
	{
		translator_postorder(tree_node_get_child(node, i));
	}

	token = (token_t *)tree_node_get_data(node);
	if (token != NULL)
		printf("%x ", token_get_class(token));
}

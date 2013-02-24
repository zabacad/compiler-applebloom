/*
 *  parser.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "parser.h"




/*
 *  Create and return a parser.
 */
parser_t *parser_create(buffer_t *buffer)
{
	parser_t *parser;


	parser = (parser_t *)malloc(sizeof(parser_t));

	parser->lexer = lexer_create(buffer);
	parser->tree = tree_create(NULL, 0);

	return parser;
}


/*
 *  
 */
void parser_destroy(parser_t *parser)
{
	lexer_destroy(parser->lexer);
	//tree_destroy(parser->tree);

	free(parser);
}


/*
 *  
 */
tree_t *parser_get_tree(parser_t *parser)
{
	return parser->tree;
}


/*
 *  
 */
void parser_parse(parser_t *parser)
{
	tree_set_root(parser->tree, parser_parse_f(parser, NULL));
}


/*
 *  
 */
static tree_node_t *parser_parse_f(parser_t *parser, token_t *pushback)
{
	token_t *token;

	tree_node_t *subtree;
	token_t *self;


	/* Create the head of the subtree. (The root of the grammar rule.) */
	self = token_create();
	token_set_class(self, T_G_F);

	subtree = tree_node_create((void *)self, sizeof(token_t));

	token_destroy(self);

	/* Determine next token (may have already been lexed but not used). */
	if (pushback != NULL)
	{
		token = pushback;
	}
	else
	{
		token = token_create();
		lexer_lex(parser->lexer, token);
	}

	/* Add children: Add terminals directly and nonterminals through their
		respective parse functions. */
	if (token_get_class(token) == T_EOF)
	{
		tree_node_add_child(subtree,
			tree_node_create((void *)token, sizeof(token_t)), -1);
	}
	else
	{
		tree_node_add_child(subtree, parser_parse_t(parser, token), -1);
		tree_node_add_child(subtree, parser_parse_f(parser, NULL), -1);
	}

	token_destroy(token);

	return subtree;
}


/*
 *  
 */
static tree_node_t *parser_parse_t(parser_t *parser, token_t *pushback)
{
	return NULL;
}


/*
 *  
 */
static tree_node_t *parser_parse_s(parser_t *parser, token_t *pushback)
{
	return NULL;
}

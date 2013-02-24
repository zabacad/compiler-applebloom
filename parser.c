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
	parser->pushback = token_create();

	return parser;
}


/*
 *  
 */
void parser_destroy(parser_t *parser)
{
	lexer_destroy(parser->lexer);
	tree_destroy(parser->tree);
	token_destroy(parser->pushback);

	free(parser);
}


/*
 *  
 */
void parser_parse(parser_t *parser)
{
	tree_set_root(parser->tree, parser_parse_t(parser));
}


/*
 *  
 */
static tree_node_t *parser_parse_f(parser_t *parser)
{
	return NULL;
}


/*
 *  
 */
static tree_node_t *parser_parse_t(parser_t *parser)
{
	return NULL;
}


/*
 *  
 */
static tree_node_t *parser_parse_s(parser_t *parser)
{
	return NULL;
}

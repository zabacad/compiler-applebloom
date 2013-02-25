/*
 *  parser.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef PARSER_H
#define PARSER_H




#include "buffer.h"
#include "lexer.h"
#include "token.h"
#include "tree.h"

#include <stdlib.h>




/* Data types. */
typedef struct parser parser_t;
struct parser
{
	lexer_t *lexer;
	tree_t *tree;
};




/* Prototypes. */
parser_t *parser_create(buffer_t *buffer);
void parser_destroy(parser_t *parser);
tree_t *parser_get_tree(parser_t *parser);
void parser_parse(parser_t *parser);
static tree_node_t *parser_parse_f(parser_t *parser, token_t *pushback);
static tree_node_t *parser_parse_t(parser_t *parser, token_t *pushback);
static tree_node_t *parser_parse_s(parser_t *parser, token_t *pushback);
static tree_node_t *parser_parse_sp(parser_t *parser, token_t *pushback);
static tree_node_t *parser_parse_spp(parser_t *parser, token_t *pushback);




#endif /* PARSER_H */

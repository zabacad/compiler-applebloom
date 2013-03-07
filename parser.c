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
	printf("Parsing\n");
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


	printf("Following grammar rule F\n");
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
		printf("Adding terminal [EOF]\n");
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
	token_t *token;

	tree_node_t *subtree;
	token_t *self;


	printf("Following grammar rule T\n");
	/* Create the head of the subtree. (The root of the grammar rule.) */
	self = token_create();
	token_set_class(self, T_G_T);

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
	if (token_get_class(token) == T_PAREN_L)
	{
		printf("Adding terminal (\n");
		tree_node_add_child(subtree,
			tree_node_create((void *)token, sizeof(token_t)), -1);

		tree_node_add_child(subtree, parser_parse_s(parser, NULL), -1);

		lexer_lex(parser->lexer, token);

		if (token_get_class(token) == T_PAREN_R)
		{
			printf("Adding terminal )\n");
			tree_node_add_child(subtree,
				tree_node_create((void *)token, sizeof(token_t)), -1);
		}
		else
		{
			printf("Parser error\n");
		}
	}
	else
	{
		printf("Parser error\n");
	}

	token_destroy(token);

	return subtree;
}


/*
 *  
 */
static tree_node_t *parser_parse_s(parser_t *parser, token_t *pushback)
{
	token_t *token;

	tree_node_t *subtree;
	token_t *self;


	printf("Following grammar rule S\n");
	/* Create the head of the subtree. (The root of the grammar rule.) */
	self = token_create();
	token_set_class(self, T_G_S);

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
	if (token_get_class(token) == T_PAREN_L)
	{
		printf("Adding terminal (\n");
		tree_node_add_child(subtree,
			tree_node_create((void *)token, sizeof(token_t)), -1);

		tree_node_add_child(subtree, parser_parse_sp(parser, NULL), -1);
	}
	if (token_get_class(token) != T_PAREN_L
		&& token_get_class(token) != T_PAREN_R)
	{
		printf("Adding terminal atom\n");
		tree_node_add_child(subtree,
			tree_node_create((void *)token, sizeof(token_t)), -1);

		tree_node_add_child(subtree, parser_parse_spp(parser, NULL), -1);
	}
	else
	{
		printf("Parser error\n");
	}

	token_destroy(token);

	return subtree;
}


/*
 *  
 */
static tree_node_t *parser_parse_sp(parser_t *parser, token_t *pushback)
{
	token_t *token;

	tree_node_t *subtree;
	token_t *self;


	printf("Following grammar rule S'\n");
	/* Create the head of the subtree. (The root of the grammar rule.) */
	self = token_create();
	token_set_class(self, T_G_SP);

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
	if (token_get_class(token) == T_PAREN_R)
	{
		printf("Adding terminal )\n");
		tree_node_add_child(subtree,
			tree_node_create((void *)token, sizeof(token_t)), -1);

		tree_node_add_child(subtree, parser_parse_spp(parser, NULL), -1);
	}
	else
	{
		tree_node_add_child(subtree, parser_parse_s(parser, token), -1);

		if (token_get_class(token) == T_PAREN_R)
		{
			printf("Adding terminal )\n");
			tree_node_add_child(subtree,
				tree_node_create((void *)token, sizeof(token_t)), -1);

			tree_node_add_child(subtree, parser_parse_spp(parser, NULL), -1);
		}
		else
		{
			printf("Parser error\n");
		}
	}

	token_destroy(token);

	return subtree;
}


/*
 *  
 */
static tree_node_t *parser_parse_spp(parser_t *parser, token_t *pushback)
{
	token_t *token;

	tree_node_t *subtree;
	token_t *self;


	printf("Following grammar rule S''\n");
	/* Create the head of the subtree. (The root of the grammar rule.) */
	self = token_create();
	token_set_class(self, T_G_SPP);

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
		respective parse functions. Look ahead to see if S applies next. */
	if (token_get_class(token) == T_PAREN_L)
	{
		tree_node_add_child(subtree, parser_parse_sp(parser, token), -1);
	}
	/* Do nothing for empty string. */

	token_destroy(token);

	return subtree;
}

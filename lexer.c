/*
 *  lexer.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "lexer.h"




int lex(buffer_t in_buffer, buffer_t out_buffer)
{
	char in;
	token_t token;

	printf("Lexing...\n");

	token = token_create();

	while (in = buffer_get_next(in_buffer))
	{
		if (in == EOF)
			break;

		if ((in == '(') || (in == ')'))
		{
			token_set_class(token, TOKEN_PAREN);
			token_set_detail(token, (void *)&in);
		}
	}

	return EXIT_SUCCESS;
}

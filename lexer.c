/*
 *  lexer.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "lexer.h"




int lex(buffer_t in_buffer, buffer_t out_buffer)
{
	char in, next;
	token_t token;

	printf("Lexing...\n");

	token = token_create();

	while (1)
	{
		in = buffer_get_next(in_buffer);
		next = buffer_peek(in_buffer);
		if (in == EOF)
			break;

		if ((in == '(') || (in == ')'))
		{
			token_set_class(token, TOKEN_PAREN);
			token_set_detail(token, (void *)&in);
		}

		token_print(token, out_buffer);
		buffer_putc(out_buffer, ' ');

		if (next == EOF)
			break;
	}

	return EXIT_SUCCESS;
}

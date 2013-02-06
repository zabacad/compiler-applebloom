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
		if (in == EOF)
			break;

		switch (in)
		{
			/* Unique characters. */
			case '(':
			case ')':
				token_set_class(token, TOKEN_PAREN);
				token_set_detail(token, (void *)&in);
				break;
			case '*':
			case '/':
			case '%':
				token_set_class(token, TOKEN_NUM_OP);
				token_set_detail(token, (void *)&in);
				break;
			case '=':
			case '<':
				token_set_class(token, TOKEN_REL);
				token_set_detail(token, (void *)&in);
				break;
			default:
				/* No new token. */
				continue;
		}

		token_print(token, out_buffer);
		buffer_putc(out_buffer, ' ');
	}

	token_destroy(token);

	return EXIT_SUCCESS;
}

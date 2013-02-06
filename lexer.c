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
	int done;
	token_t token;
	union
	{
		char c;
		int i;
		double d;
	} value;

	printf("Lexing...\n");

	done = 0;
	token = token_create();

	while (!done)
	{
		in = buffer_get_next(in_buffer);
		if (in == EOF)
		{
			done = 1;
			break;
		}

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
			/* Might be an op, might be a num. */
			case '-':
			case '+':
				next = buffer_peek(in_buffer);
				if (next == EOF)
					done = 1;
				/* Assume + or - immediatly followed by a digit is a number. */
				if (next == '0'
					|| next == '1'
					|| next == '2'
					|| next == '3'
					|| next == '4'
					|| next == '5'
					|| next == '6'
					|| next == '7'
					|| next == '8'
					|| next == '9')
				{
					value.i = 0xff;
					token_set_class(token, TOKEN_INT);
					token_set_detail(token, (void *)&value);
				}
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

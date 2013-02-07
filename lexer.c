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
					/* `parse_num' needs to see the + or -. */
					buffer_seek(in_buffer, -1);
					parse_num(token, in_buffer);
				}
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				/* `parse_num' needs to see the first digit. */
				buffer_seek(in_buffer, -1);
				parse_num(token, in_buffer);
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


void parse_num(token_t token, buffer_t buffer)
{
	char in;
	int done;

	int neg;
	int real;

	int whole;
	int fraction;
	double complete;


	done = 0;

	real = 0;
	neg = 0;

	whole = 0;
	fraction = 0;
	complete = 0;

	in = buffer_get_next(buffer);
	switch (in)
	{
		case '-':
			in = buffer_get_next(buffer);
			whole = digit(in);
			neg = 1;
			break;
		case '+':
			in = buffer_get_next(buffer);
			whole = digit(in);
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			whole = digit(in);
			break;
		default:
			return;
	}


	while (!done && !real)
	{
		in = buffer_get_next(buffer);
		switch (in)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				whole *= 10;
				whole += digit(in);
				break;
			case '.':
				real = 1;
				break;
			default:
				buffer_seek(buffer, -1);
				done = 1;
		}
	}

	while(!done && real)
	{
		in = buffer_get_next(buffer);
		switch (in)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				fraction *= 10;
				fraction += digit(in);
				break;
			default:
				buffer_seek(buffer, -1);
				done = 1;
		}
	}

	if (real)
	{
		complete = fraction;
		while (complete >= 1)
		{
			complete /= 10;
		}
		complete += whole;

		if (neg)
			complete = -complete;

		token_set_class(token, TOKEN_REAL);
		token_set_detail(token, (void *)&complete);
	}
	else
	{
		if (neg)
			whole = -whole;

		token_set_class(token, TOKEN_INT);
		token_set_detail(token, (void *)&whole);
	}
}

int digit(char digit)
{
	/* In ASCII, it suffices to subtract 0x30. This works, too. */
	switch (digit)
	{
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
	}

	/* Fail. */
	return -1;
}

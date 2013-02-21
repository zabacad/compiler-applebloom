/*
 *  lexer.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "lexer.h"




/*
 *  Create and return a lexer.
 */
lexer_t *lexer_create(buffer_t *in)
{
	lexer_t *lexer;


	lexer = (lexer_t *)malloc(sizeof(lexer_t));
	lexer->lookback = '\0';
	lexer->buffer = in;

	return lexer;
}


/*
 *  Destroy a lexer.
 */
void lexer_destroy(lexer_t *lexer)
{
	free(lexer);
}


/*
 *  Get the next token.
 */
void lexer_lex(lexer_t *lexer, token_t *token)
{
	int s_ready;
	int i;
	int s_len;
	int s_cap;
	char *s;

	int token_ready;


	s_ready = 0;
	i = 0;
	s_cap = LEXER_STR_BLOCK;
	s = (char *)malloc(s_cap * sizeof(char));

	token_ready = 0;

	/* Get the first char (special case). */
	if (lexer->lookback != '\0')
	{
		s[i] = lexer->lookback;
		lexer->lookback = '\0';
	}
	else
	{
		s[i] = buffer_get_next(lexer->buffer);
	}

	/* Skip leading whitespace. */
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r')
		s[i] = buffer_get_next(lexer->buffer);

	/* Stop on delimter. */
	switch (s[i])
	{
		case '(':
		case ')':
			s[++i] = '\0';
			s_ready = 1;
			break;
		case EOF:
			token_set_class(token, T_EOF);
			return;
	}

	while (!s_ready)
	{
		i++;

		if (i >= s_cap)
		{
			s_cap += LEXER_STR_BLOCK;
			s = (char *)realloc(s, s_cap * sizeof(char));
		}

		s[i] = buffer_get_next(lexer->buffer);

		/* Stop on delimter. */
		switch (s[i])
		{
			case '(':
			case ')':
				lexer->lookback = s[i];
				s[i] = '\0';
				s_ready = 1;
				break;
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				s[i] = '\0';
				s_ready = 1;
				break;
		}
	}

	token_print(token, stdout);
	printf(": \"%s\"\n", s);

	token_ready = 1;

	free(s);

	if (!token_ready)
		token_set_class(token, T_NULL);
}


/*
 *  Convert a string to a number.
 */
static void num(char *s, token_t *token)
{
	int i;
	int len;

	int is_neg;
	int is_real;

	int whole;
	int fraction;
	double complete;


	i = 0;
	len = strlen(s);

	is_neg = 0;
	is_real = 0;

	whole = 0;
	fraction = 0;
	complete = 0;

	switch (s[i])
	{
		case '-':
			is_neg = 1;
		case '+':
			i++;
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
			whole = digit(s[i++]);
			break;
		default:
			token_set_class(token, T_NULL);
			return;
	}


	while ((i < len) && !is_real)
	{
		switch (s[i++])
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
				whole += digit(s[i]);
				break;
			case '.':
				is_real = 1;
				break;
			default:
				token_set_class(token, T_NULL);
				return;
		}
	}

	while((i < len) && is_real)
	{
		switch (s[i++])
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
				fraction += digit(s[i]);
				break;
			default:
				token_set_class(token, T_NULL);
				return;
		}
	}

	if (is_real)
	{
		complete = fraction;
		while (complete >= 1)
			complete /= 10;
		complete += whole;

		if (is_neg)
			complete = -complete;

		token_set_class(token, T_REAL);
		token_set_detail(token, (void *)&complete);
	}
	else
	{
		if (is_neg)
			whole = -whole;

		token_set_class(token, T_INT);
		token_set_detail(token, (void *)&whole);
	}
}


/*
 *  Convert a char digit to an int.
 */
static int digit(char digit)
{
	if (digit >= 0x30 && digit <= 0x39)
		return (int)(digit - 0x30);

	return -1;
}








/*
 *  Lex
 */
token_t *lex(char *s)
{
	int len;

	token_t *token;
	union
	{
		char c;
		int i;
		double r;
		char *s;
	} detail;


	len = strlen(s);

	token = token_create();

	if (strcmp(s, "println") == 0)
		token->class = T_KW_PRINT;
	else if (strcmp(s, "if") == 0)
		token->class = T_KW_PRINT;
	else if (strcmp(s, "while") == 0)
		token->class = T_KW_PRINT;
	else if (strcmp(s, "let") == 0)
		token->class = T_KW_PRINT;
	else if (strcmp(s, "assign") == 0)
		token->class = T_KW_PRINT;
	else if (strcmp(s, "bool") == 0)
		token->class = T_KW_PRINT;
	else if (strcmp(s, "int") == 0)
		token->class = T_KW_PRINT;
	else if (strcmp(s, "real") == 0)
		token->class = T_KW_PRINT;
	else if (strcmp(s, "string") == 0)
		token->class = T_KW_PRINT;
	else if (strcmp(s, "false") == 0)
		token->class = T_BOOL_F;
	else if (strcmp(s, "true") == 0)
		token->class = T_BOOL_T;
	else if (strcmp(s, "and") == 0)
		token->class = T_BOOL_OP_AND;
	else if (strcmp(s, "or") == 0)
		token->class = T_BOOL_OP_OR;
	else if (strcmp(s, "not") == 0)
		token->class = T_BOOL_OP_NOT;
	else if (strcmp(s, "iff") == 0)
		token->class = T_BOOL_OP_IFF;
	else if (strcmp(s, "=") == 0)
		token->class = T_RELATE_EQ;
	else if (strcmp(s, "<") == 0)
		token->class = T_RELATE_LT;
	else if (strcmp(s, "+") == 0)
		token->class = T_OP_ADD_CAT;
	else if (strcmp(s, "-") == 0)
		token->class = T_NUM_OP_SUB;
	else if (strcmp(s, "*") == 0)
		token->class = T_NUM_OP_MUL;
	else if (strcmp(s, "/") == 0)
		token->class = T_NUM_OP_DIV;
	else if (strcmp(s, "%") == 0)
		token->class = T_NUM_OP_MOD;
	else if (strcmp(s, "^") == 0)
		token->class = T_NUM_OP_POW;
	else if (strcmp(s, "logn") == 0)
		token->class = T_REAL_OP_LOGN;
	/*else if (strcmp(s, "true") == 0)
		token->class = T_REAL_OP_EPOW;*/
	else if (strcmp(s, "sin") == 0)
		token->class = T_REAL_OP_SIN;
	else if (strcmp(s, "cos") == 0)
		token->class = T_REAL_OP_COS;
	else if (strcmp(s, "tan") == 0)
		token->class = T_REAL_OP_TAN;
	/*else if (strcmp(s, "") == 0)
		token->class = T_STR;*/

	switch (s[0])
	{
		/*case ' ':
		case '\t':
		case '\r':
			continue;*/
		/* Count lines. */
		/*case '\n':
			buffer_inc_line(in_buffer);
			continue;*/
		/* Unique characters. */
		/*case '(':
			token_set_class(token, T_PAREN_L);
			token_set_detail(token, (void *)&in);
			break;
		case ')':
			token_set_class(token, T_PAREN_R);
			token_set_detail(token, (void *)&in);
			break;
		case '*':
		case '/':
		case '%':
			token_set_class(token, T_NUM_OP);
			token_set_detail(token, (void *)&in);
			break;
		case '=':
		case '<':
			token_set_class(token, T_REL);
			token_set_detail(token, (void *)&in);
			break;*/
		/* Might be an op, might be a num. */
		/*case '-':
		case '+':
			next = buffer_peek(in_buffer);
			if (next == EOF)
				done = 1;*/
			/* Assume + or - immediatly followed by a digit is a number. */
			/*if (next == '0'
				|| next == '1'
				|| next == '2'
				|| next == '3'
				|| next == '4'
				|| next == '5'
				|| next == '6'
				|| next == '7'
				|| next == '8'
				|| next == '9')
			{*/
				/* `parse_num' needs to see the + or -. */
				/*buffer_seek(in_buffer, -1);
				parse_num(token, in_buffer);
			}
			else
			{
				token_set_class(token, T_NUM_OP);
				token_set_detail(token, (void *)&in);
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
		case '9':*/
			/* `parse_num' needs to see the first digit. */
			/*buffer_seek(in_buffer, -1);
			parse_num(token, in_buffer);
			break;*/
		/* Everything else is a string. */
		/*default:
			buffer_seek(in_buffer, -1);\
			parse_str(token, in_buffer);*/
	}

	return token;
}


/*
 *  
 */
/*void parse_str(token_t *token, buffer_t buffer)
{
	char in;
	int done;

	char *str;
	int index;


	done = 0;

	str = (char *)malloc(256 * sizeof(char));
	index = 0;

	token_set_class(token, T_STR);

	in = buffer_get_next(buffer);
	if (in == '"')
	{
		while (!done && (index < 255))
		{
			in = buffer_get_next(buffer);
			if (in == '"')
			{
				str[index++] = '\0';
				done = 1;
			}
			else
				str[index++] = in;
		}
	}
	else
	{
		str[index++] = in;
		while (!done && (index < 255))
		{
			in = buffer_get_next(buffer);
			if (in == ' ' || in == '\t' || in == '\n' || in == '\r')
			{
				str[index++] = '\0';
				done = 1;
			}
			else
			{
				str[index++] = in;
			}
		}
	}

	token_set_detail(token, (void *)str);
}*/

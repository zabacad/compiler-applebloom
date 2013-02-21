/*
 *  token.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "token.h"




/*
 *  Create and return an empty token.
 */
token_t *token_create()
{
	token_t *token;


	token = (token_t *)malloc(sizeof(token_t));
	token->class = T_NULL;

	return token;
}


/*
 *  Destory `token' and all its data.
 */
void token_destroy(token_t *token)
{
	if (token->class == T_STR)
		free(token->detail.s);

	free(token);
}


/*
 *  Change the class of `token'.
 */
void token_set_class(token_t *token, int class)
{
	if (token->class == T_STR)
		free(token->detail.s);

	token->class = class;
	if (token->class == T_STR)
		token->detail.s = NULL;
}


/*
 *  Change the detail of `token'. `detail' points to the data, whatever type it
 *  is, and is cast based on the token's class.
 */
void token_set_detail(token_t *token, void *detail)
{
	size_t data_size;


	switch (token->class)
	{
		case T_INT:
			token->detail.i = *(int *)detail;
			break;
		case T_REAL:
			token->detail.r = *(double *)detail;
			break;
		case T_STR:
			free((void *)token->detail.s);
			data_size = strlen(detail) + 1;
			token->detail.s = (char *)malloc(data_size * sizeof(char));
			memcpy((void *)token->detail.s, detail, data_size);
			break;
	}
}


/*
 *  Get the class of `token'.
 */
int token_get_class(token_t *token)
{
	return token->class;
}


/*
 *  Set the `line' where the `token' was encountered.
 */
void token_set_line(token_t *token, int line)
{
	token->line = line;
}


/*
 *  Set the `col' where the `token' was encountered.
 */
void token_set_col(token_t *token, int col)
{
	token->col = col;
}


/*
 *  Print `token' to `stream' in a human-readable form.
 */
void token_print(token_t *token, FILE *stream)
{
	switch (token->class)
	{
		case T_PAREN_L:
			fprintf(stream, "<paren: (>");
			break;
		case T_PAREN_R:
			fprintf(stream, "<paren: )>");
			break;
		case T_INT:
			fprintf(stream, "<int:   %d>", token->detail.i);
			break;
		case T_REAL:
			fprintf(stream, "<real:  %lf>", token->detail.r);
			break;
		case T_STR:
			fprintf(stream, "<str:   %s>", token->detail.s);
			break;
		default:
			fprintf(stream, "<other: %d>", token->class);
	}
}

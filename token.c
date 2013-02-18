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
	token->class = TOKEN_NULL;

	return token;
}


/*
 *  Destory `token' and all its data.
 */
void token_destroy(token_t *token)
{
	if (token->class == TOKEN_STR)
		free(token->detail.s);

	free(token);
}


/*
 *  Change the class of `token'.
 */
void token_set_class(token_t *token, int class)
{
	if (token->class == TOKEN_STR)
		free(token->detail.s);

	token->class = class;
	if (token->class == TOKEN_STR)
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
		case TOKEN_PAREN_L:
		case TOKEN_PAREN_R:
		case TOKEN_BOOL:
		case TOKEN_BOOL_OP:
		case TOKEN_NUM_OP:
		case TOKEN_REAL_OP:
		case TOKEN_STR_OP:
		case TOKEN_REL:
			token->detail.c = *(char *)detail;
			break;
		case TOKEN_INT:
			token->detail.i = *(int *)detail;
			break;
		case TOKEN_REAL:
			token->detail.r = *(double *)detail;
			break;
		case TOKEN_STR:
			free((void *)token->detail.s);
			data_size = strlen(detail) + 1;
			token->detail.s = (char *)malloc(data_size * sizeof(char));
			memcpy((void *)token->detail.s, detail, data_size);
			break;
	}
}


/*
 *  Print `token' to `buffer' in a human-readable form.
 */
void token_print(token_t *token, buffer_t buffer)
{
	FILE *stream;


	stream = buffer_get_stream(buffer);

	fprintf(stream, "<");

	switch (token->class)
	{
		case TOKEN_PAREN_L:
		case TOKEN_PAREN_R:
			fprintf(stream, "paren, %c", token->detail.c);
			break;
		case TOKEN_BOOL:
			fprintf(stream, "bool, %c", token->detail.c);
			break;
		case TOKEN_BOOL_OP:
			fprintf(stream, "bool op, %c", token->detail.c);
			break;
		case TOKEN_INT:
			fprintf(stream, "int, %d", token->detail.i);
			break;
		case TOKEN_REAL:
			fprintf(stream, "real, %lf", token->detail.r);
			break;
		case TOKEN_NUM_OP:
			fprintf(stream, "num op, %c", token->detail.c);
			break;
		case TOKEN_REAL_OP:
			fprintf(stream, "real op, %c", token->detail.c);
			break;
		case TOKEN_STR:
			fprintf(stream, "string, %s", token->detail.s);
			break;
		case TOKEN_STR_OP:
			fprintf(stream, "string op, %c", token->detail.c);
			break;
		case TOKEN_REL:
			fprintf(stream, "relation, %c", token->detail.c);
			break;
		default:
			fprintf(stream, "???");
	}

	fprintf(stream, ">");
}

/*
 *  token.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "token.h"




token_t token_create()
{
	token_t token;


	token = malloc(sizeof(token_t));
	token->class = TOKEN_NULL;

	return token;
}


void token_destroy(token_t token)
{
	free(token);
}


void token_set_class(token_t token, int class)
{
	token->class = class;
}


void token_set_detail(token_t token, void *detail)
{
	switch (token->class)
	{
		case TOKEN_PAREN:
		case TOKEN_BOOL:
		case TOKEN_BOOL_OP:
		case TOKEN_NUM_OP:
		case TOKEN_REAL_OP:
		case TOKEN_STR_OP:
		case TOKEN_REL:
			token->detail = (union token_detail_t)*(char *)detail;
			break;
		case TOKEN_INT:
			token->detail = (union token_detail_t)*(int *)detail;
			break;
		case TOKEN_REAL:
			token->detail = (union token_detail_t)*(double *)detail;
			break;
		case TOKEN_STR:
			/* TODO */
			break;
	}
}


void token_print(token_t token, buffer_t buffer)
{
	FILE *stream;


	stream = buffer_get_stream(buffer);

	fprintf(stream, "<");

	switch (token->class)
	{
		case TOKEN_PAREN:
			fprintf(stream, "paren, %c", token->detail.paren_detail);
			break;
		case TOKEN_BOOL:
			fprintf(stream, "bool, %c", token->detail.bool_detail);
			break;
		case TOKEN_BOOL_OP:
			fprintf(stream, "bool op, %c", token->detail.bool_op_detail);
			break;
		case TOKEN_INT:
			fprintf(stream, "int, %d", token->detail.int_detail);
			break;
		case TOKEN_REAL:
			fprintf(stream, "real, %lf", token->detail.real_detail);
			break;
		case TOKEN_NUM_OP:
			fprintf(stream, "num op, %c", token->detail.num_op_detail);
			break;
		case TOKEN_REAL_OP:
			fprintf(stream, "real op, %c", token->detail.real_op_detail);
			break;
		case TOKEN_STR:
			fprintf(stream, "string, %s", token->detail.str_detail);
			break;
		case TOKEN_STR_OP:
			fprintf(stream, "string op, %c", token->detail.str_op_detail);
			break;
		case TOKEN_REL:
			fprintf(stream, "relation, %c", token->detail.rel_detail);
			break;
		default:
			fprintf(stream, "???");
	}

	fprintf(stream, ">");
}

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
		case TOKEN_STR:
		case TOKEN_STR_OP:
		case TOKEN_REL:
			token->detail = (union token_detail_t)*(char *)detail;
			break;
		case TOKEN_INT:
		case TOKEN_REAL:
			token->detail = (union token_detail_t)*(double *)detail;
			break;
	}
}

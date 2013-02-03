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
	token->detail = (union token_detail_t)*(char *)detail;
}

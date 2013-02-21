/*
 *  lexer.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef LEXER_H
#define LEXER_H




#include "buffer.h"
#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/* Constant settings. */
#define LEXER_STR_BLOCK 16




/* Data types. */
typedef struct lexer lexer_t;
struct lexer
{
	buffer_t *buffer;
	char lookback;
	int line;
	int col;
};




/* Prototypes. */
lexer_t *lexer_create(buffer_t *in);
void lexer_destroy(lexer_t *lexer);
void lexer_lex(lexer_t *lexer, token_t *token);

static void num(char *s, token_t *token);
static int digit(char digit);




#endif /* LEXER_H */

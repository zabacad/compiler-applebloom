/*
 *  token.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef TOKEN_H
#define TOKEN_H




#include "buffer.h"

#include <string.h>




/* Symbolic constants. */
/* Token classes. */
#define TOKEN_NULL 0x00
#define TOKEN_PAREN_L 0x01
#define TOKEN_PAREN_R 0x02
#define TOKEN_BOOL 0x03
#define TOKEN_BOOL_OP 0x04
#define TOKEN_INT 0x05
#define TOKEN_REAL 0x06
#define TOKEN_NUM_OP 0x07
#define TOKEN_REAL_OP 0x08
#define TOKEN_STR 0x09
#define TOKEN_STR_OP 0x0A
#define TOKEN_REL 0x0B

/* Detail symbols. */
#define BOOL_F 'f'
#define BOOL_T 't'
#define BOOL_OP_AND '&'
#define BOOL_OP_OR '|'
#define BOOL_OP_IFF 'v'
#define BOOL_OP_NOT '~'
#define REAL_OP_SIN 's'
#define REAL_OP_COS 'c'
#define REAL_OP_TAN 't'
#define REAL_OP_LOGN 'l'
#define REAL_OP_EXP 'e'




/* Data types. */
typedef struct token token_t;

struct token
{
	int class;
	union
	{
		char c;
		int i;
		double r;
		char *s;
	} detail;
	int line;
	int col;
};




/* Prototypes. */
token_t *token_create();
void token_destroy(token_t *token);
void token_set_class(token_t *token, int class);
void token_set_detail(token_t *token, void *detail);
void token_print(token_t *token, buffer_t buffer);




#endif /* TOKEN_H */

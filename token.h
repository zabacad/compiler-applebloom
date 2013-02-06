/*
 *  token.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef TOKEN_H
#define TOKEN_H




#include "buffer.h"




/* Symbolic constants. */
/* Classes of tokens. */
#define TOKEN_NULL 0x00
#define TOKEN_PAREN 0x01
#define TOKEN_BOOL 0x02
#define TOKEN_BOOL_OP 0x03
#define TOKEN_INT 0x04
#define TOKEN_REAL 0x05
#define TOKEN_NUM_OP 0x06
#define TOKEN_REAL_OP 0x07
#define TOKEN_STR 0x08
#define TOKEN_STR_OP 0x09
#define TOKEN_REL 0x0A

/* Constants to save details when input does not fit. */
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

/* Size to start and increment printable buffers. */
#define PRINT_BUFF_INIT 0x08
#define PRINT_BUFF_STEP 0x08




/* Data types. */
/* Token details depend on token class. */
union token_detail_t
{
	char paren_detail;
	char bool_detail;
	char bool_op_detail;
	int int_detail;
	double real_detail;
	char num_op_detail;
	char real_op_detail;
	char *str_detail;
	char str_op_detail;
	char rel_detail;
};

/* Any one token. */
struct token
{
	/* The overarching class of the token. One of `TOKEN_*'. */
	int class;
	/* The input data is stored here when possible, or mapped to a constant. */
	union token_detail_t detail;
};
typedef struct token *token_t;




/* Prototypes. */
token_t token_create();
void token_destroy(token_t token);
void token_set_class(token_t token, int class);
void token_set_detail(token_t token, void *detail);
void token_print(token_t token, buffer_t buffer);




#endif /* TOKEN_H */

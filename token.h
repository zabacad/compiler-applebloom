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
#define T_NULL 0x00
#define T_PAREN_L 0x01
#define T_PAREN_R 0x02
#define T_KW_PRINT 0x03
#define T_KW_IF 0x04
#define T_KW_WHILE 0x05
#define T_KW_LET 0x06
#define T_KW_ASSIGN 0x07
#define T_KW_BOOL 0x08
#define T_KW_INT 0x09
#define T_KW_REAL 0x0A
#define T_KW_STR 0x0B
#define T_BOOL_F 0x0C
#define T_BOOL_T 0x0D
#define T_BOOL_OP_AND 0x0E
#define T_BOOL_OP_OR 0x0F
#define T_BOOL_OP_NOT 0x10
#define T_BOOL_OP_IFF 0x11
#define T_RELATE_EQ 0x12
#define T_RELATE_LT 0x13
#define T_OP_ADD_CAT 0x14
#define T_NUM_OP_SUB 0x15
#define T_NUM_OP_MUL 0x16
#define T_NUM_OP_DIV 0x17
#define T_NUM_OP_MOD 0x18
#define T_NUM_OP_POW 0x19
#define T_REAL_OP_LOGN 0x1A
#define T_REAL_OP_EPOW 0x1B
#define T_REAL_OP_SIN 0x1C
#define T_REAL_OP_COS 0x1D
#define T_REAL_OP_TAN 0x1E
#define T_INT 0x1F
#define T_REAL 0x20
#define T_STR 0x21
#define T_EOF 0x22

/* Psuedo-tokens representing grammar rules on the parse tree. */
#define T_G_F 0x80
#define T_G_T 0x81
#define T_G_S 0x82
#define T_G_SP 0x83
#define T_G_SPP 0x84




/* Data types. */
typedef struct token token_t;

struct token
{
	int class;
	union
	{
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
int token_get_class(token_t *token);
void token_set_line(token_t *token, int line);
void token_set_col(token_t *token, int col);
void token_print(token_t *token, FILE *stream);




#endif /* TOKEN_H */

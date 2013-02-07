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




int lex(buffer_t in_buffer, buffer_t out_buffer);
void parse_num(token_t token, buffer_t buffer);
int digit(char digit);
void parse_str(token_t token, buffer_t buffer);




#endif /* LEXER_H */

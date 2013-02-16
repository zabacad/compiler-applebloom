/*
 *  main.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef MAIN_H
#define MAIN_H




/* Headers. */
#include "buffer.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/* Actions to be performed. Stages must be in order. */
#define ACT_NULL 0x00
#define ACT_USAGE 0x01
#define ACT_LEX 0x02
#define ACT_PARSE 0x03




#endif /* MAIN_H */

/*
 *  buffer.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef BUFFER_H
#define BUFFER_H




#include <stdio.h>




/* Data types. */
struct buffer
{
	FILE *stream;
	int line;
	int col;
};
typedef struct buffer *buffer_t;




/* Prototypes. */
buffer_t buffer_create(FILE *stream);
void buffer_destory(buffer_t buffer);
int buffer_seek(buffer_t butter, int offset);
char buffer_get(buffer_t buffer);
char buffer_get_next(buffer_t buffer);
char buffer_peek(buffer_t buffer);
void buffer_putc(buffer_t buffer, char what);
void buffer_puts(buffer_t buffer, char *what);
void buffer_inc_line(buffer_t buffer);
int buffer_get_line(buffer_t buffer);
int buffer_get_col(buffer_t buffer);
FILE *buffer_get_stream(buffer_t buffer);




#endif /* BUFFER_H */

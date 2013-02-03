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
};
typedef struct buffer *buffer_t;




/* Prototypes. */
buffer_t buffer_create(FILE *stream);
void buffer_destory(buffer_t buffer);
int buffer_seek(buffer_t butter, int offset);
char buffer_get(buffer_t buffer);
char buffer_get_next(buffer_t buffer);
char buffer_peek(buffer_t buffer);
void buffer_put(buffer_t buffer, char what);
void buffer_put(buffer_t buffer, char *what);




#endif /* BUFFER_H */

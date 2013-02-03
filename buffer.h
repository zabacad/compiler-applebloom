/*
 *  buffer.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef BUFFER_H
#define BUFFER_H




#include <stdio.h>




struct buffer
{
	FILE *stream;
};
typedef struct buffer *buffer_t;




buffer_t buffer_create(FILE *stream);
void buffer_destory(buffer_t buffer);




#endif /* BUFFER_H */

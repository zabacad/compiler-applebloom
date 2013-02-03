/*
 *  buffer.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "buffer.h"




buffer_t buffer_create(FILE *stream)
{
	buffer_t buffer;


	buffer = malloc(sizeof(struct buffer));
	buffer->stream = stream;

	return buffer;
}


void buffer_destory(buffer_t buffer)
{
	free(buffer);
}

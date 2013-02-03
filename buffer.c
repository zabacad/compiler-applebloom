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


	/* Validate. */
	if (stream == NULL)
	{
		return NULL;
	}

	/* Create buffer. */
	buffer = malloc(sizeof(struct buffer));
	buffer->stream = stream;

	return buffer;
}


void buffer_destory(buffer_t buffer)
{
	free(buffer);
}


int buffer_seek(buffer_t buffer, int offset)
{
	return fseek(buffer->stream, offset, SEEK_CUR);
}


char buffer_get_next(buffer_t buffer)
{
	buffer_seek(buffer, 1);
	return buffer_get(buffer);
}


char buffer_peek_next(buffer_t buffer)
{
	char next;


	buffer_seek(buffer, 1);
	next = buffer_get(buffer);
	buffer_seek(buffer, -1);

	return next;
}


char buffer_get(buffer_t buffer)
{
	return (char)fgetc(buffer->stream);
}


void buffer_put_next(buffer_t buffer, char what)
{
}


void buffer_put(buffer_t buffer, char what)
{
}

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
	buffer->line = 1;
	buffer->col = 1;

	return buffer;
}


void buffer_destory(buffer_t buffer)
{
	free(buffer);
}


int buffer_seek(buffer_t buffer, int offset)
{
	buffer->col += offset;
	return fseek(buffer->stream, offset, SEEK_CUR);
}


char buffer_get(buffer_t buffer)
{
	char c;


	c = buffer_get_next(buffer);
	buffer_seek(buffer, -1);

	return c;
}


char buffer_get_next(buffer_t buffer)
{
	buffer->col++;
	return fgetc(buffer->stream);
}


char buffer_peek(buffer_t buffer)
{
	char c;


	buffer_seek(buffer, 1);
	c = buffer_get(buffer);
	buffer_seek(buffer, -1);

	return c;
}


void buffer_putc(buffer_t buffer, char what)
{
	fputc(what, buffer->stream);
}


void buffer_puts(buffer_t buffer, char *what)
{
	fputs(what, buffer->stream);
}


void buffer_inc_line(buffer_t buffer)
{
	buffer->line++;
	buffer->col = 0;
}


int buffer_get_line(buffer_t buffer)
{
	return buffer->line;
}


int buffer_get_col(buffer_t buffer)
{
	return buffer->col;
}


FILE *buffer_get_stream(buffer_t buffer)
{
	return buffer->stream;
}

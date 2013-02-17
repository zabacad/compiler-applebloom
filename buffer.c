/*
 *  buffer.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "buffer.h"




/*
 *  Create and return a buffer around `stream'.
 */
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


/*
 *  Destory a buffer.
 */
void buffer_destory(buffer_t buffer)
{
	free(buffer);
}


/*
 *  Move `offset' characters forward (or backward, it `offset' is negative) in
 *  `buffer'.
 */
int buffer_seek(buffer_t buffer, int offset)
{
	buffer->col += offset;
	return fseek(buffer->stream, offset, SEEK_CUR);
}


/*
 *  Return the current character from `buffer'
 */
char buffer_get(buffer_t buffer)
{
	char c;


	c = buffer_get_next(buffer);
	buffer_seek(buffer, -1);

	return c;
}


/*
 *  Return the current character from `buffer' and move to the next.
 */
char buffer_get_next(buffer_t buffer)
{
	buffer->col++;
	return fgetc(buffer->stream);
}


/*
 *  Return the next character from `buffer'.
 */
char buffer_peek(buffer_t buffer)
{
	char c;


	buffer_seek(buffer, 1);
	c = buffer_get(buffer);
	buffer_seek(buffer, -1);

	return c;
}


/*
 *  Put `what' in the buffer and move to the next position.
 */
void buffer_putc(buffer_t buffer, char what)
{
	fputc(what, buffer->stream);
}


/*
 *  Put `what' in the buffer and move to the next position.
 */
void buffer_puts(buffer_t buffer, char *what)
{
	fputs(what, buffer->stream);
}


/*
 *  Record that the buffer is now on the next line.
 */
void buffer_inc_line(buffer_t buffer)
{
	buffer->line++;
	buffer->col = 0;
}


/*
 *  Return the current line number.
 */
int buffer_get_line(buffer_t buffer)
{
	return buffer->line;
}


/*
 *  Return the current column number.
 */
int buffer_get_col(buffer_t buffer)
{
	return buffer->col;
}


/*
 *  Return the stream which `buffer' is wrapping.
 */
FILE *buffer_get_stream(buffer_t buffer)
{
	return buffer->stream;
}

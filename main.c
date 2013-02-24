/*
 *  main.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "main.h"




/*
 *  Command-line front end for compiler.
 */
int main(int argc, char **argv)
{
	int action;

	int arg;

	buffer_t *in_buffer;
	buffer_t *out_buffer;

	int is_done;
	lexer_t *lexer;
	token_t *token;


	/* Set default settings. */
	action = ACT_LEX;
	in_buffer = buffer_create(stdin);
	out_buffer = buffer_create(stdout);

	/* Parse command-line arguments. */
	for (arg = 1; arg < argc; arg++)
	{
		if ((strcmp(argv[arg], "--help") == 0)
			|| (strcmp(argv[arg], "-h") == 0))
		{
			action = ACT_USAGE;
		}
		else if ((strcmp(argv[arg], "--lex") == 0) && (action <= ACT_LEX))
		{
			action = ACT_LEX;
		}
		else if ((strcmp(argv[arg], "--parse") == 0) && (action <= ACT_PARSE))
		{
			action = ACT_PARSE;
		}
		else
		{
			fprintf(stderr, "Invalid argument: %s\n", argv[arg]);
			/* Stop parsing command-line. */
			arg = argc;

			action = ACT_USAGE;
		}
	}

	/* Take action. */
	if (action == ACT_USAGE)
	{
		printf(
			"Usage: compiler [option...]\n"
			"\n"
			"  Options:\n"
			"\n"
			"  -h, --help   Display this help text.\n"
			"      --lex    Run the lexer.\n"
			"      --parse  Run the parseer. (Calls the lexer.)\n"
		);
	}
	else if (action == ACT_LEX)
	{
		is_done = 0;
		lexer = lexer_create(in_buffer);
		token = token_create();

		while (!is_done)
		{
			lexer_lex(lexer, token);
			token_print(token, stdout);
			printf("\n");
			if (token_get_class(token) == T_EOF)
				is_done = 1;
		}

		token_destroy(token);
		lexer_destroy(lexer);

		return EXIT_SUCCESS;
	}
	else if (action == ACT_PARSE)
	{
		return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;
}

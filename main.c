/*
 *  main.c
 *
 *  Ian Shearin
 *  CS480
 */




#include "main.h"




int main(int argc, char **argv)
{
	char *in_filename;
	FILE in_file;
	char *out_filename;
	FILE out_file;

	int action;

	int arg;


	/* Set default settings. */
	//in_file = (FILE)NULL;
	//out_file = (FILE)NULL;
	action = ACT_LEX;

	/* Parse command-line arguments. */
	for (arg = 1; arg < argc; arg++)
	{
		if ((strcmp(argv[arg], "--help") == 0)
			|| (strcmp(argv[arg], "-h") == 0))
		{
			action = ACT_USAGE;
		}
		else if ((strcmp(argv[arg], "--lex") == 0))
		{
			action = ACT_LEX;
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
			"Usage: compiler [option...] [infile]\n"
			"\n"
			"  Options:\n"
			"\n"
			"  -h, --help  Display this help text.\n"
			"      --lex   Run the lexer.\n"
		);
	}
	else if (action == ACT_LEX)
	{
		printf("Lexing...\n");
	}

	return EXIT_SUCCESS;
}

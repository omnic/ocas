// ocas
// the OmniC assembler
//
// Copyright 2013 Haneef Mubarak
// All Rights Reserved

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "ocas.h"

int main (int argc, char **argv) {
	if (argc != 2) {
		int exitcode = 3;
		if (argc == 0) { //	Odd...
			fputs ("Your system configuration is not supported:\n", stderr);
			fputs ("Arguments are not being passed correctly.\n", stderr);
		} else if (argc == 1) {
			ocas_error_help (1);
			exitcode = 2;
		} else {
			ocas_error_toomanyargs (argc);
		}
		exit (exitcode);
	}

	char *invocation = strrchr (argv[0], '/');
	invocation += 3;	// Get to the start of the command name
	switch (*invocation) {
		case 'a':	// "ocas"
			assert (invocation = malloc (1));
			*invocation = 0;
			break;
		case 'd':	// "ocdis"
			assert (invocation = malloc (1));
			*invocation = 1;
			break;
		default :
			fputs ("Bad invocation: \"", stderr);
			invocation -= 2;
			fputs (invocation, stderr);
			fputs ("\"\n", stderr);
			ocas_error_help (2);
	}

	return 0;
}

int ocas_error_help (int error) {
	switch (error) {
		case 1:
			fputs ("You need to supply a file to process\n", stderr);
			fputs ("Something like `ocas file` is what you want to do\n", stderr);
			break;
		case 2:
			fputs ("Command invocation is not `ocas` or `ocdis`\n", stderr);
			break;
		default:
			assert (NULL); // This version of ocas seems to be messed up
			break;
	}
	return error;
}

int ocas_error_toomanyargs (int argc) {
	printf ("Looks like you had %i args too many.\n", argc - 2);
	return argc;
}

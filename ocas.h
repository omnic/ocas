// Declarations for anything that goes
// in the main file

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/file.h>

#include <fcntl.h>

typedef struct {
	uint32_t	line;
	uint32_t	file;

	unsigned int	isComment		:1;	// We don't need to process comments
	unsigned int	isSpecial		:1;	// Handle special instructions differently
} sourceLine;

int ocas_error_help	(int error);
int ocas_error_toomanyargs (int argc);

int as	(char *argv);

// that's all folks

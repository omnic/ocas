// Declarations for anything that goes
// in the main file

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

int ocas_error_help	(int error);
int ocas_error_toomanyargs (int argc);

int as	(char **argv);

// that's all folks

// as
// the assembler part of ocas

#include "as.h"

int as (char **argv) {
	int source_fd = -1;
	assert ((source_fd = open (argv[1], O_RDONLY, 0) != -1);
	assert (flock (source_fd, LOCK_EX) != -1);	// File can't change while we read

	struct stat *statbuf;
	assert (statbuf = malloc (sizeof statbuf));
	assert (fstat (infile_fd, statbuf));

	char *source_ptr = mmap (NULL, statbuf->st_size, PROT_READ,
					MAP_FILE | MAP_SHARED, source_fd, 0);
	assert (source_ptr != MAP_FAILED);

	

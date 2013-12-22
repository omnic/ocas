// as
// the assembler part of ocas

#include "as.h"

mapFileStruct mainsource_file;
void *mainfile;

#if 0	// exclude until complete
int as (char **argv) {
	int x;

	// Set the settings for the mainfile mmap
	mainsource_file.m_prot	= PROT_READ;
	mainsource_file.m_flag	= MAP_FILE | MAP_SHARED;
	mainsource_file.o_flag	= O_RDONLY;
	mainsource_file.lock	= LOCK_EX;
	mainsource_file.offset	= 0;
	// mmap the mainfile
	if (x = mmapFile (argv[1], &mainsource_file)) {
		// couldn't open the mainfile, explain and GTFO

		fputs ("ocas->as->mmapFile:\t", stderr);

		// switch on the error
		switch (x) {
			case -1:	// open failed
				fputs ("Could not open file:", stderr);
				break;
			case -2:	// locking failed
				fputs ("Failed to obtain an exclusive lock on file:", stderr);
				break;
			case -3:	// fstat failed
				fputs ("stat failed on file:", stderr);
				break;
			case -4:
				fputs ("Was not able to memory map file:", stderr);
				break;
			default:
				fprintf (stderr, "Unknown error (%i) occurred with file:", x);
				break;
		}

		fprintf (stderr, "\t'%s'\n", argv[1]);
		return -2; // file error
	}
}
#endif

int mmapFile (char *filename, mapFileStruct *mapfile) {
	int  x;

	struct stat statbuf;

	mapfile->fd = -1;
	if ((mapfile->fd = open (filename, mapfile->o_flag)) == -1) {
		return -1;	// open failed
	}

	if (flock (mapfile->fd, mapfile->lock) == -1) {
		do {
			x = close (mapfile->fd);
		} while ((x != 0) && (errno == EINTR));

		return -2;	// locking failed
	}

	if (!fstat (mapfile->fd, &statbuf) == 0) {
		do {
			x = close (mapfile->fd);
		} while ((x != 0) && (errno == EINTR));

		return -3;	// fstat failed
	}

	mapfile->len = statbuf.st_size;
	mapfile->addr = mmap (NULL, mapfile->len, mapfile->m_prot,
				mapfile->m_flag, mapfile->fd,
				mapfile->offset);
	if (!(mapfile->addr)) {
		do {
			x = close (mapfile->fd);
		} while ((x != 0) && (errno == EINTR));

		return -4;	// mmap failed
	}

	return 0;
}

int munmapFile (mapFileStruct *mapfile) {
	int x;

	if (!munmap (mapfile->addr, mapfile->len)) {
		return -1;	// munmap failed
	}

	do {
		x = close (mapfile->fd);
	} while ((x != 0) && (errno == EINTR));

	return 0;
}

int mremapFile (off_t newSize, mapFileStruct *mapfile) {
	int status = 0;

	if (!ftruncate (mapfile->fd, newSize)) {
		return -1;	// ftruncate failed
	}

	void *addr = mmap (NULL, newSize, mapfile->m_prot,
				mapfile->m_flag, mapfile->fd,
				mapfile->offset);
	if (!addr) {
		return -2;	// mmap new range failed
	}

	if (!munmap (mapfile->addr, mapfile->len)) {
		status = 1;	// munmap old range failed
	}

	mapfile->addr = addr;
	mapfile->len = newSize;

	return status;
}

#pragma once
#include "ocas.h"

#pragma pack(push,1)

typedef struct {
	void	*addr;
	size_t	len;
	int	prot;
	int	flags;
	int	fd;
	off_t	offset;
} mapFileStruct;

#pragma pack(pop)

int mmapFile		(char *filename, mapFileStruct *mFS);
int mremapFile		(off_t newSize, mapFileStruct *mFS);
int munmapFile		(mapFileStruct *mFS);


#pragma once
#include "ocas.h"

#pragma pack(push,1)

typedef struct {
	void	*addr;
	size_t	len;
	int	m_prot;
	int	m_flag;
	int	o_flag;
	int	lock;
	int	fd;
	off_t	offset;
} mapFileStruct;

#pragma pack(pop)

int mmapFile		(char *filename, mapFileStruct *mapfile);
int mremapFile		(off_t newSize, mapFileStruct *mapfile);
int munmapFile		(mapFileStruct *mapfile);

int getlines		(char *string, char ***lines, int *linecount);

#pragma once
#include "FS.h"

class FAT16 :
	public FS
{
private:
	#pragma pack(push, 1)
	typedef struct {
		BYTE Padding1[11];
		BYTE sectorSize[2];
		BYTE clasterSize[1];
	} BootRecord;
	#pragma pack(pop)
protected:
	// В разных ФС различается только процесс получения размера кластера
	bool ReadClusterSize();
};


#pragma once
#include "FS.h"
class NTFS :
	public FS
{
private:
#pragma pack(push, 1)
	typedef struct {
		unsigned char Padding1[10];
		unsigned char sectorSize[2];
		unsigned char clasterSize[1];
	} BootRecord;
#pragma pack(pop)
protected:
	// В разных ФС различается только процесс получения размера кластера
	bool ReadClusterSize();

};


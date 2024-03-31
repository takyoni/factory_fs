#pragma once
#include "FS.h"
class EFAT :
	public FS
{
private:
#pragma pack(push, 1)
	typedef struct {
		DWORD Padding1[11];
		DWORD sectorSize[2];
		DWORD clasterSize[1];
	} BootRecord;
#pragma pack(pop)
protected:
	bool ReadClusterSize();
};


#pragma once
#include "FS.h"
#include <iostream>
#include <cstdint>
#include <cstring>
class NTFS :
	public FS
{
private:
	#pragma pack(push, 1)
	typedef struct {
		uint8_t jumpInstruction[3];
		char oemID[8];
		uint16_t bytesPerSector;
		uint8_t sectorsPerCluster;
	} BootRecord;
	#pragma pack(pop)
protected:
	// В разных ФС различается только процесс получения размера кластера
	bool ReadClusterSize();

};


#include "FAT16.h"
#include <iostream>
#include "windows.h"
#include "stdio.h"
using namespace std;

bool FAT16::ReadClusterSize()
{
    BYTE sector[512];
    DWORD bytesRead;
    DWORD bytesToRead = sizeof(sector);

    LARGE_INTEGER sectorSizeOffset;
    sectorSizeOffset.QuadPart = 0;

    if (!SetFilePointerEx(fileHandler, sectorSizeOffset, NULL, FILE_BEGIN)) {
        throw std::invalid_argument("Set FilePointer error");
        CloseHandle(fileHandler);
        return false;
    }
    if (!ReadFile(fileHandler, sector, bytesToRead, &bytesRead, NULL))
    {
        throw std::invalid_argument("ReadFile error");
        CloseHandle(fileHandler);
        return false;
    }

    BootRecord* pBootRecord = reinterpret_cast<BootRecord*>(sector);
    unsigned int sectorSize = (pBootRecord->sectorSize[1] << 8) | pBootRecord->sectorSize[0];
    unsigned int countSectors = static_cast<int>(pBootRecord->clasterSize[0]);
    clusterSize = sectorSize * countSectors;
    return true;
}
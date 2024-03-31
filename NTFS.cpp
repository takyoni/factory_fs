#include "NTFS.h"
#include <iostream>
#include "windows.h"
#include "stdio.h"
using namespace std;

bool NTFS::ReadClusterSize()
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
    unsigned int value;
    std::memcpy(&value, pBootRecord->sectorSize, sizeof(unsigned int));
    unsigned int countSectors = static_cast<unsigned int>(sector[13]);
    unsigned int sectorSize = (sector[12] << 8) | sector[11];
 //   unsigned int countSectors = static_cast<unsigned int>(sector[13]);
    clusterSize = sectorSize * countSectors;
    return true;
}


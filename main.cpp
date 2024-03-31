#include <iostream>
#include "FS.h"
#include "NTFS.h"
#include "FAT16.h"
#include "EFAT.h"
#include "HFS+.h"
#include "windows.h"
#include <iomanip>
#include "MyFSC.h"
#include "FileSystemCreator.h"
using namespace std;

void hexdump(const BYTE* array, unsigned int length, unsigned int offset) {
    const int bytes_per_line = 16;
    for (size_t i = 0; i < length; i += bytes_per_line) {
        // Вывод адреса текущей строки
        std::cout << std::setw(8) << std::setfill('0') << std::hex << offset + i << ": ";

        // Вывод байтов в шестнадцатеричном формате
        for (int j = 0; j < bytes_per_line; ++j) {
            if (i + j < length) {
                std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(array[i + j]) << " ";
            }
            else {
                std::cout << "   "; // для неполных строк
            }
        }

        // Вывод символов ASCII
        std::cout << "  ";
        for (int j = 0; j < bytes_per_line; ++j) {
            if (i + j < length) {
                char c = array[i + j];
                std::cout << (c >= 32 && c < 127 ? c : '.');
            }
            else {
                std::cout << " "; // для неполных строк
            }
        }

        std::cout << std::endl;
    }
}
FSEnum DetectFS(LPCWSTR device) {
    HANDLE fileHandler = CreateFileW(
        device,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (fileHandler == INVALID_HANDLE_VALUE)
    {
        throw std::invalid_argument("Error INVALID_HANDLE_VALUE!");
    }
    DWORD bytesRead;
    BYTE buffer[2048];
    // Читаем первые 2048 байт
    if (!ReadFile(fileHandler, buffer, sizeof(buffer), &bytesRead, nullptr)) {
        throw "Error reading volume\n";
    }

    // Проверяем сигнатуру NTFS
    BYTE ntfsSignature[] = { 0x4E, 0x54, 0x46, 0x53 };
    if (memcmp(buffer + 3, ntfsSignature, sizeof(ntfsSignature)) == 0) {
        return FSEnum::NTFS;
    }
    // Проверяем сигнатуру FAT16
    BYTE fat16Signature[] = { 0x1C, 0xEB, 0x52, 0x90 };
    if (memcmp(buffer + 11, fat16Signature, sizeof(fat16Signature)) == 0) {
        return FSEnum::FAT16;
    }
    // Проверяем сигнатуру ExFAT
    BYTE exfatSignature[] = { 0x45, 0x78, 0x46, 0x41, 0x54 };
    if (memcmp(buffer + 3, exfatSignature, sizeof(exfatSignature)) == 0) {
        return FSEnum::ExFAT;
    }
    // Проверяем сигнатуру HFS+
    BYTE hfsPlusSignature[] = { 0x48, 0x2B, 0x0E, 0x0E };
    if (memcmp(buffer + 1024, hfsPlusSignature, sizeof(hfsPlusSignature)) == 0) {
        return FSEnum::HFSp;
    }
    throw "Cannot detect fs!";
}
int main()
{

    // NTFS
    FileSystemCreator* fsCreator = new MyFSC;
    FSEnum fsType = DetectFS(L"\\\\.\\C:");
    FS* fs = fsCreator->CreateFileSystem(fsType, L"\\\\.\\C:");
    if (!fs->Init(L"\\\\.\\C:")) {
        cout << "Init: " << GetLastError();
        return false;
    };
    unsigned int clusterSize = fs->ClusterSize();
    unsigned int clusterNumber = 5;
    BYTE * cluster = new BYTE[clusterSize];

    if (!fs->ReadCluster(clusterNumber, cluster)) {
        cout << "Read cluster error: " << GetLastError();
        return false;
    };

    hexdump(cluster, clusterSize, clusterNumber * clusterSize);
    cout << "Cluster size per bytes: " << dec << clusterSize << endl;

    delete[] cluster;
}

#pragma once
#include "FileSystemCreator.h"
#include "FS.h"
#include "Windows.h"
enum class FSEnum { NTFS, ExFAT, FAT16, HFSp };
class FileSystemCreator
{
public:
	FS* CreateFileSystem(FSEnum, LPCWSTR);
};
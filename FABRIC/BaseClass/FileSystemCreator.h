#pragma once
#include "FileSystemCreator.h"
#include "FS.h"
#include "Windows.h"
enum class FSEnum { NTFS, ExFAT, FAT16, HFSp };
class FileSystemCreator
{
public:
	virtual FS* CreateFileSystem(FSEnum, LPCWSTR) = 0;
};
#pragma once
#include "FileSystemCreator.h"

class MyFSC :
	public FileSystemCreator
{
	FS* CreateFileSystem(FSEnum, LPCWSTR);
};


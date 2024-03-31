#pragma once
#include "FABRIC/BaseClass/FileSystemCreator.h"

class MyFSC :
	public FileSystemCreator
{
	FS* CreateFileSystem(FSEnum, LPCWSTR);
};


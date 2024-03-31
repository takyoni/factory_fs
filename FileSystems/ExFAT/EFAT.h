#pragma once
#include "FileSystems/BaseFS/FS.h"
class EFAT :
	public FS
{
protected:
	bool ReadClusterSize();
};


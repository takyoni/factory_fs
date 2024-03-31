#pragma once
#include "FS.h"
class EFAT :
	public FS
{
protected:
	bool ReadClusterSize();
};


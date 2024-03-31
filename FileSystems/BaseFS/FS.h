#include "windows.h"
#pragma once
class FS
{
protected:
	HANDLE fileHandler = NULL;
	unsigned int clusterSize = {0};
	virtual bool ReadClusterSize();
public:
	bool Init(LPCWSTR);
	bool ReadCluster(unsigned int, BYTE*);
	unsigned int ClusterSize() const { return clusterSize; };
	virtual ~FS();
};
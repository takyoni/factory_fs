#include "FileSystemCreator.h"
#include "Windows.h"
#include "FS.h"
#include "NTFS.h"
#include "FAT16.h"
#include "EFAT.h"
#include "HFS+.h"
#include <stdexcept>
FS* FileSystemCreator::CreateFileSystem(FSEnum fsType, LPCWSTR path)
{
	switch (fsType) {
	case FSEnum::NTFS: {
		NTFS* fs = new NTFS();
		fs->Init(path);
		return fs;
	}
	case FSEnum::FAT16: {
		FAT16* fs = new FAT16();
		fs->Init(path);
		return fs;
	}
	case FSEnum::ExFAT: {
		EFAT* fs = new EFAT();
		fs->Init(path);
		return fs;
	}
	case FSEnum::HFSp: {
		HFSP* fs = new HFSP();
		fs->Init(path);
		return fs;
	}
	default:
		throw std::invalid_argument("Set FilePointer error");
		return NULL;
	}
}


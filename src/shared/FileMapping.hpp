#pragma once

#include "shared/Exception.h"


#ifndef NOMINMAX 
#define NOMINMAX
#endif
#include <windows.h>
#include <string>


namespace RLBotBM {

template <typename T>
struct FileMapping {
	FileMapping(const std::string name, bool create) {
		if (create) {
			hMapFile = CreateFileMapping(
				INVALID_HANDLE_VALUE,    // use paging file
				NULL,                    // default security
				PAGE_READWRITE,          // read/write access
				0,                       // maximum object size (high-order DWORD)
				sizeof(T),               // maximum object size (low-order DWORD)
				name.c_str());
		} else {
			hMapFile = OpenFileMapping(
				FILE_MAP_ALL_ACCESS,   // read/write access
				FALSE,                 // do not inherit the name
				name.c_str());
		}
		if (!hMapFile) {
			if (create)
				throw CreateFileMappingException();
			else
				throw OpenFileMappingException();

		}
		
	}

	~FileMapping() {
		CloseHandle(hMapFile);
	}
	
	HANDLE hMapFile;
};



template <typename T>
struct FileMappingView {
	FileMappingView(FileMapping<T>& fileMapping) {
		mem = (T*)MapViewOfFile(fileMapping.hMapFile,   // handle to map object
			FILE_MAP_ALL_ACCESS, // read/write permission
			0,
			0,
			sizeof(T));
		
		if (mem == NULL)
			throw MapViewOfFileException();
	}

	~FileMappingView() {
		UnmapViewOfFile((LPCTSTR)mem);
	}
	
	T* mem;

	inline T* operator->() const {
		return mem;
	}

	inline operator T() const {
		return *mem;
	}
};

}
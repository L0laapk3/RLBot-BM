#pragma once


#ifndef NOMINMAX 
#define NOMINMAX
#endif
#include <windows.h>
#include <string>

namespace RLBotBM::Shared {

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
		if (!hMapFile)
			throw std::exception();
		
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
			throw std::exception();
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
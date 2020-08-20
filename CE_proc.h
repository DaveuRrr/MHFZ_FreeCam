#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <vector>

namespace proc
{
	// AOB Version
	DWORD GetProcID(wchar_t* exeName);
	MODULEENTRY32 GetModule(DWORD dwProcID, wchar_t* moduleName);
	uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
	uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
}



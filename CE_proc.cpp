#include "CE_proc.h"

// Proc ID
DWORD proc::GetProcID(wchar_t* exeName)
{
	PROCESSENTRY32 procEntry = { 0 };
	HANDLE hSnapshot = (CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));

	if (!hSnapshot) return 0;
	procEntry.dwSize = sizeof(procEntry);

	if (!Process32First(hSnapshot, &procEntry)) return 0;
	do
	{
		if (!wcscmp(procEntry.szExeFile, exeName))
		{
			CloseHandle(hSnapshot);
			return procEntry.th32ProcessID;
		}
	} while (Process32Next(hSnapshot, &procEntry));

	CloseHandle(hSnapshot);
	return 0;
}

// AOB Version
MODULEENTRY32 proc::GetModule(DWORD dwProcID, wchar_t* moduleName)
{
	MODULEENTRY32 modEntry = { 0 };
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{

		modEntry.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, moduleName)) break;
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modEntry;
}

// Base Pointer Version
uintptr_t proc::GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

// Find Address from Pointer
uintptr_t proc::FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}
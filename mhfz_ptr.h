#pragma once
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>

void InitializeScan(wchar_t* exeName);

namespace mhfz
{
	extern DWORD procID;
	extern HANDLE hProcess;
	extern uintptr_t moduleBase;

	namespace Camera
	{
		// Base Address
		extern uintptr_t ADR;

		//NOP instructions
		extern uintptr_t Xnop;
		extern uintptr_t Ynop;
		extern uintptr_t Znop;
		// Add more?

		// Offset of Pointers
		extern std::vector<unsigned int> offSetX;
		extern std::vector<unsigned int> offSetY;
		extern std::vector<unsigned int> offSetZ;
		extern std::vector<unsigned int> offSetA;

		// Value of the Pointer
		extern uintptr_t X;
		extern uintptr_t Y;
		extern uintptr_t Z;
		extern uintptr_t A;
	}
	namespace Key
	{
		// Camera
		extern int left;
		extern int right;
		extern int up;
		extern int down;
		extern int backward;
		extern int forward;
		extern int speedUp;
		extern int speedDown;

		// Toggles
		extern int Free;
	}
	namespace Check
	{
		extern bool Free;
	}
}
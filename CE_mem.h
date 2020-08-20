#pragma once
#include <windows.h>
#include <vector>
#include <tlhelp32.h>
#include <tchar.h>

namespace mem
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
}
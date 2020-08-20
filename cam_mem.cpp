#include "cam_mem.h"
#include "CE_mem.h"
#include "mhfz_ptr.h"

void CAM::NOP()
{
	// Value Pointer, Size, Process
	mem::NopEx((BYTE*)mhfz::Camera::Xnop, 0, mhfz::hProcess);
	mem::NopEx((BYTE*)mhfz::Camera::Ynop, 0, mhfz::hProcess);
	mem::NopEx((BYTE*)mhfz::Camera::Znop, 0, mhfz::hProcess);
}

void CAM::Patch()
{
	mem::PatchEx((BYTE*)mhfz::Camera::Xnop, (BYTE*)"\x00\x00\x00\x00", 4, mhfz::hProcess);
	mem::PatchEx((BYTE*)mhfz::Camera::Ynop, (BYTE*)"\x00\x00\x00\x00", 4, mhfz::hProcess);
	mem::PatchEx((BYTE*)mhfz::Camera::Znop, (BYTE*)"\x00\x00\x00\x00", 4, mhfz::hProcess);
}
#include "mhfz_ptr.h"
#include "CE_proc.h"

void InitializeScan(wchar_t* exeName)
{
	// Get Process
	mhfz::procID = proc::GetProcID(exeName);
	mhfz::hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, mhfz::procID);
	mhfz::moduleBase = proc::GetModuleBaseAddress(mhfz::procID, (const wchar_t*)exeName);

	// this is what MonsterHunter?????.exe+00000000
	mhfz::Camera::ADR = mhfz::moduleBase + 0x00000000;
	// NOP Addresses
	mhfz::Camera::Xnop = mhfz::moduleBase + 0x00000000;
	mhfz::Camera::Ynop = mhfz::moduleBase + 0x00000000;
	mhfz::Camera::Znop = mhfz::moduleBase + 0x00000000;
	// Offsets
	mhfz::Camera::offSetX = { 0x00, 0x00 };
	mhfz::Camera::offSetY = { 0x00, 0x00 };
	mhfz::Camera::offSetZ = { 0x00, 0x00 };
	mhfz::Camera::offSetA = { 0x00, 0x00 };
	// Values
	mhfz::Camera::X = proc::FindDMAAddy(mhfz::hProcess, mhfz::Camera::ADR, mhfz::Camera::offSetX);
	mhfz::Camera::Y = proc::FindDMAAddy(mhfz::hProcess, mhfz::Camera::ADR, mhfz::Camera::offSetY);
	mhfz::Camera::Z = proc::FindDMAAddy(mhfz::hProcess, mhfz::Camera::ADR, mhfz::Camera::offSetZ);
	mhfz::Camera::A = proc::FindDMAAddy(mhfz::hProcess, mhfz::Camera::ADR, mhfz::Camera::offSetA);
}

DWORD mhfz::procID;
HANDLE mhfz::hProcess;
uintptr_t mhfz::moduleBase;

uintptr_t mhfz::Camera::ADR;

//NOP instructions
uintptr_t mhfz::Camera::Xnop;
uintptr_t mhfz::Camera::Ynop;
uintptr_t mhfz::Camera::Znop;
// Add more?

// Offset of Pointers
std::vector<unsigned int> mhfz::Camera::offSetX;
std::vector<unsigned int> mhfz::Camera::offSetY;
std::vector<unsigned int> mhfz::Camera::offSetZ;
std::vector<unsigned int> mhfz::Camera::offSetA;

// Value of the Pointer
uintptr_t mhfz::Camera::X;
uintptr_t mhfz::Camera::Y;
uintptr_t mhfz::Camera::Z;
uintptr_t mhfz::Camera::A;

// Camera Keys
int mhfz::Key::left = 0x00;
int mhfz::Key::right = 0x00;
int mhfz::Key::up = 0x00;
int mhfz::Key::down = 0x00;
int mhfz::Key::backward = 0x00;
int mhfz::Key::forward = 0x00;
int mhfz::Key::speedUp = 0x00;
int mhfz::Key::speedDown = 0x00;

// Toggles
int mhfz::Key::Free = 0x00;

// Check Bool
bool mhfz::Check::Free;

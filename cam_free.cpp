#include "cam_free.h"
#include "mhfz_ptr.h"

//Added by Asterisk for Multiple Inputs
std::valarray<float> Free::FreeCam(float angle, float speed)
{
	std::valarray<float> V0{ 0, 0, 0 };
	std::valarray<float> V2{ -cos(angle), 0, -sin(angle) };
	std::valarray<float> V1{ sin(angle), 0, -cos(angle) };
	std::valarray<float> V3{ 0, 1, 0 };

	V1 = V1 * speed;
	V2 = V2 * speed;
	V3 = V3 * speed;

	if (GetAsyncKeyState(mhfz::Key::left)) V0 += -V2;
	if (GetAsyncKeyState(mhfz::Key::right)) V0 += V2;
	if (GetAsyncKeyState(mhfz::Key::forward)) V0 += -V1;
	if (GetAsyncKeyState(mhfz::Key::backward)) V0 += V1;
	if (GetAsyncKeyState(mhfz::Key::up)) V0 += V3;
	if (GetAsyncKeyState(mhfz::Key::down)) V0 += -V3;
	return V0;
}

//Added by Asterisk for Multiple Inputs
std::valarray<float> Free::PersCam(float speed)
{
	if (GetAsyncKeyState(mhfz::Key::left)) return std::valarray<float> {+speed, 0, 0};
	if (GetAsyncKeyState(mhfz::Key::right)) return std::valarray<float> {-speed, 0, 0};
	if (GetAsyncKeyState(mhfz::Key::forward)) return std::valarray<float> {0, 0, +speed};
	if (GetAsyncKeyState(mhfz::Key::backward)) return std::valarray<float> {0, 0, -speed};
	if (GetAsyncKeyState(mhfz::Key::up)) return std::valarray<float> {0, +speed, 0};
	if (GetAsyncKeyState(mhfz::Key::down)) return std::valarray<float> {0, -speed, 0};
	return std::valarray<float> {0, 0, 0};
}

void Free::UpdateCam(float x, float y, float z)
{
	WriteProcessMemory(mhfz::hProcess, (BYTE*)mhfz::Camera::X, &x, sizeof(x), nullptr);	// Free Cam X
	WriteProcessMemory(mhfz::hProcess, (BYTE*)mhfz::Camera::Y, &y, sizeof(y), nullptr);	// Free Cam X
	WriteProcessMemory(mhfz::hProcess, (BYTE*)mhfz::Camera::Z, &z, sizeof(z), nullptr);	// Free Cam X
}

float Free::UpdateSpeed(float speed)
{
	if (GetAsyncKeyState(mhfz::Key::speedUp)) speed = speed + 0.25;
	if (GetAsyncKeyState(mhfz::Key::speedDown)) speed = speed - 0.25;
	return speed;
}
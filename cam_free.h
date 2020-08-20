#pragma once
#include <valarray>

namespace Free
{
	std::valarray<float> FreeCam(float angle, float speed);
	std::valarray<float> PersCam(float speed);

	void UpdateCam(float x, float y, float z);
	float UpdateSpeed(float speed);
}


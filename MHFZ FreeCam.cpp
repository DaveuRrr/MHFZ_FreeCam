// MHFZ FreeCam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "mhfz_ptr.h"
#include "cam_free.h"
#include "cam_mem.h"

# define M_PI           3.14159265358979323846  /* pi */

int main()
{
    std::cout << "Hello GraveYard!\n";

    //Initialize Scan
    InitializeScan((wchar_t*)L"MonsterHunterFrontier.exe");
    float x;
    float y;
    float z;
    float a; //Angle
    float r; //Radian
    float speed = 10;

    while (true)
    {
        // Toggle Free Cam
        if (GetAsyncKeyState(mhfz::Key::Free))
        {
            mhfz::Check::Free = !mhfz::Check::Free;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        // Start Free Cam
        if (mhfz::Check::Free)
        {
            // Read Values
            speed = Free::UpdateSpeed(speed);
            ReadProcessMemory(mhfz::hProcess, (BYTE*)mhfz::Camera::X, &x, sizeof(x), nullptr);
            ReadProcessMemory(mhfz::hProcess, (BYTE*)mhfz::Camera::Y, &y, sizeof(y), nullptr);
            ReadProcessMemory(mhfz::hProcess, (BYTE*)mhfz::Camera::Z, &z, sizeof(z), nullptr);
            ReadProcessMemory(mhfz::hProcess, (BYTE*)mhfz::Camera::A, &a, sizeof(a), nullptr);
            // Updates the Camera Values
            r = -((a * M_PI) / 180);
            std::valarray<float> p{ x, y, z };
            p += Free::FreeCam(r, speed);

            // pass the values from Valarray
            x = p[0];
            y = p[1];
            z = p[2];

            // Update the Values to the game
            Free::UpdateCam(x, y, z);
        }
        // Take a Breather
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

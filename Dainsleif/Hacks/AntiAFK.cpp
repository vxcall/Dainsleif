#include "../pch.h"
#include "AntiAFK.h"
#include <thread>

using namespace std::literals::chrono_literals;

void AntiAFK::MakeMeaninglessMoves()
{
    int* forceBackward = reinterpret_cast<int*>(Modules::client + dwForceBackward);
    int* forceForward = reinterpret_cast<int*>(Modules::client + dwForceForward);
    int* forceRight = reinterpret_cast<int*>(Modules::client + dwForceRight);
    int* forceLeft = reinterpret_cast<int*>(Modules::client + dwForceLeft);
    int* forceJump = reinterpret_cast<int*>(Modules::client + dwForceJump);

    *forceBackward = 1;
    std::this_thread::sleep_for(1s);
    *forceBackward = 0;

    *forceForward = 1;
    std::this_thread::sleep_for(1s);
    *forceForward = 0;

    *forceJump = 5;

    *forceLeft = 1;
    std::this_thread::sleep_for(1.5s);
    *forceLeft = 0;
    *forceJump = 4;

    *forceRight = 1;
    std::this_thread::sleep_for(1.5s);
    *forceRight = 0;
}

void AntiAFK::Run(bool *bAntiAFK) {
    while(*bAntiAFK) {
        std::this_thread::sleep_for(50s);
        if (*bAntiAFK) { // Checking if bAntiAFK hasn't been changed to false during this sleep.
            MakeMeaninglessMoves();
        }
    }
}
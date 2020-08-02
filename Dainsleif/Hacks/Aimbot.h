#pragma once

#include "../pch.h"
#include "../LocalPlayer.h"

namespace Aimbot
{
    //AimBot lets local player aim at enemy's head with full precision.
    void Run(std::vector<Entity*> entityList);
}
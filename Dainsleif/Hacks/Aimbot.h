#pragma once

#include "../pch.h"
#include "../Player.h"

namespace Aimbot
{
    //AimBot lets local player aim at enemy's head with full precision.
    void Run(std::vector<Player*> playerList);
}
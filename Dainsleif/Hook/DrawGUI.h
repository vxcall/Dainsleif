#pragma once

#include <string>

enum Hack_label {
    ALL,
    AIMBOT,
    GLOWHACK,
    ANTIRECOIL,
    TRIGGERBOT,
    ANTIAFK,
    FOV
};

void ShowMenuBar();
void ShowTabMenu();
static void HelpMarker(char* title, std::string desc);

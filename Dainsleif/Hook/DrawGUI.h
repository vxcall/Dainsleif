#pragma once

#include <string>
#include <map>

enum Hack_label {
    ALL,
    AIMBOT,
    GLOWHACK,
    ANTIRECOIL,
    TRIGGERBOT,
    ANTIAFK,
    FOV,
    ESP,
    MINIMAPHACK
};

void ShowMenuBar(std::map<std::string, bool>& visibleHacks);
void ShowTabMenu(std::map<std::string, bool>& visibleHacks);
void HelpMarker(const char* title, const std::string& desc);

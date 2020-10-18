#include "TabState.h"

//When you add new tab, modify visibleHacks in GraphicHook.cpp
void TabState::Save(std::string& filename)
{
        const toml::value data = visibleHacks;
        std::ofstream file;
        file.open(filename, std::ios::out);
        file << data;
        file.close();
}

void TabState::Fetch(std::string& filename)
{
    auto prevTabState = toml::parse(filename);
    t_aimBot = toml::find_or(prevTabState, "Aim Bot", true);
    t_glowHack = toml::find_or(prevTabState, "Glow Hack", true);
    t_antiRecoil = toml::find_or(prevTabState, "Anti Recoil", true);
    t_triggerBot = toml::find_or(prevTabState, "Trigger Bot", true);
    t_antiAFK = toml::find_or(prevTabState, "Anti AFK", false);
    t_fov = toml::find_or(prevTabState, "Fov", false);
    t_esp = toml::find_or(prevTabState, "Esp", false);
    t_minimapHack = toml::find_or(prevTabState, "Minimap Hack", false);
}
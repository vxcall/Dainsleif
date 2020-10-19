#include "TabStateToml.h"

//When you add new tab, modify visibleHacks in GraphicHook.cpp
void TabStateToml::Save(std::string& filename)
{
        const toml::value data = visibleHacks;
        std::ofstream file;
        file.open(filename, std::ios::out);
        file << data;
        file.close();
}

void TabStateToml::Fetch(std::string& filename)
{
    auto prevTabState = toml::parse(filename);
    TabFlags::t_aimBot = toml::find_or(prevTabState, "Aim Bot", true);
    TabFlags::t_glowHack = toml::find_or(prevTabState, "Glow Hack", true);
    TabFlags::t_antiRecoil = toml::find_or(prevTabState, "Anti Recoil", true);
    TabFlags::t_triggerBot = toml::find_or(prevTabState, "Trigger Bot", true);
    TabFlags::t_antiAFK = toml::find_or(prevTabState, "Anti AFK", false);
    TabFlags::t_fov = toml::find_or(prevTabState, "Fov", false);
    TabFlags::t_esp = toml::find_or(prevTabState, "Esp", false);
    TabFlags::t_minimapHack = toml::find_or(prevTabState, "Minimap Hack", false);
}
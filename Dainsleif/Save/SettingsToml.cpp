#include "SettingsToml.h"


extern ImVec4 enemyGlowColor, localGlowColor;
extern bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot, bAntiAFK, bMinimapHack; //declared in dllmain.cpp
extern bool bEsp, bLineOverlay, bRectOverlay; //declared in GraphicHook.main
extern float aimSmoothness; //declared in Hacks/Aimbot.cpp
extern int fov; //declared in dllmain.cpp
extern float range;

void SettingsToml::ReadSettings(std::string& filename)
{
    auto saveData = toml::parse(filename);

    // find specified values associated with one keys, and assign them into each variable.
    bAimbot = toml::find_or<bool>(saveData, "bAimbot", Default::bAimbot);
    aimSmoothness = toml::find_or(saveData, "aimSmoothness", Default::aimSmoothness);
    range = toml::find_or(saveData, "range", Default::range);
    bGlowHack = toml::find_or<bool>(saveData, "bGlowHack", Default::bGlowhack);
    bAntiRecoil = toml::find_or<bool>(saveData, "bAntiRecoil", Default::bAntiRecoil);
    bTriggerBot = toml::find_or<bool>(saveData, "bTriggerBot", Default::bTriggerBot);
    bAntiAFK = toml::find_or<bool>(saveData, "bAntiAFK", Default::bAntiAFK);
    fov = toml::find_or(saveData, "fov", Default::fov);
    bEsp = toml::find_or(saveData, "bEsp", Default::bEsp);
    bLineOverlay = toml::find_or(saveData, "bLineOverlay", Default::bLineOverlay);
    bRectOverlay = toml::find_or(saveData, "bRectOverlay", Default::bRectOverlay);
    bMinimapHack = toml::find_or(saveData, "bMinimapHack", Default::bMinimapHack);

    auto& enemyGlowColorTable = toml::find_or(saveData, "enemyGlowColor", {});
    enemyGlowColor = ImVec4(toml::find_or(enemyGlowColorTable, "Red", Default::enemyGlowColor.x), toml::find_or(enemyGlowColorTable, "Green", Default::enemyGlowColor.y), toml::find_or(enemyGlowColorTable, "Blue", Default::enemyGlowColor.z), toml::find_or(enemyGlowColorTable, "Alpha", Default::enemyGlowColor.w));

    auto& localGlowColorTable = toml::find_or(saveData, "localGlowColor", {});
    localGlowColor = ImVec4(toml::find_or(localGlowColorTable, "Red", Default::localGlowColor.x), toml::find_or(localGlowColorTable, "Green", Default::localGlowColor.y), toml::find_or(localGlowColorTable, "Blue", Default::localGlowColor.z), toml::find_or(localGlowColorTable, "Alpha", Default::localGlowColor.w));

}

void SettingsToml::WriteSettings(std::string& filename)
{
    //Make a variable that holds keys and values.
    const toml::value data{{"bAimbot", bAimbot}, {"bGlowHack", bGlowHack},
                           {"bAntiRecoil", bAntiRecoil}, {"bTriggerBot", bTriggerBot}, {"bAntiAFK", bAntiAFK}, {"fov", fov},
                           {"enemyGlowColor",    {{"Red", enemyGlowColor.x}, {"Green", enemyGlowColor.y}, {"Blue", enemyGlowColor.z}, {"Alpha", enemyGlowColor.w}}},
                           {"localGlowColor",    {{"Red", localGlowColor.x}, {"Green", localGlowColor.y}, {"Blue", localGlowColor.z}, {"Alpha", localGlowColor.w}}},
                           {"aimSmoothness", aimSmoothness}, {"range", range},
                           {"bEsp", bEsp}, {"bLineOverlay", bLineOverlay}, {"bRectOverlay", bRectOverlay},
                           {"bMinimapHack", bMinimapHack}
    };
    //Open file and write it in toml syntax.
    std::ofstream file;
    file.open(filename, std::ios::out);
    file << data;
    file.close();
}


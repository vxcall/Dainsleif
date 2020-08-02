#include "pch.h"
#include "RWtoml.h"

ImVec4 enemyGlowColor, localGlowColor;
extern bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot; //declared in dllmain.cpp
extern float aimSmoothness; //declared in Hacks/Aimbot.cpp
extern int fov;

void RWtoml::ParseFile(std::string filename) {
    auto saveData = toml::parse(filename);

    // find specified values associated with one keys, and assign them into each variable.
    bAimbot = toml::find_or<bool>(saveData, "bAimbot", false);
    aimSmoothness = toml::find_or<float>(saveData, "aimSmoothness", 0.2f);
    bGlowHack = toml::find_or<bool>(saveData, "bGlowHack", false);
    bAntiRecoil = toml::find_or<bool>(saveData, "bAntiRecoil", false);
    bTriggerBot = toml::find_or<bool>(saveData, "bTriggerBot", false);
    fov = toml::find_or<int>(saveData, "fov", 90);

    auto& enemyGlowColorTable = toml::find_or(saveData, "enemyGlowColor", {});
    enemyGlowColor = ImVec4(toml::find_or<float>(enemyGlowColorTable, "Red", 0.8f), toml::find_or<float>(enemyGlowColorTable, "Green", 0.1f), toml::find_or<float>(enemyGlowColorTable, "Blue", 0.15f), toml::find_or<float>(enemyGlowColorTable, "Alpha", 1.0f));

    auto& localGlowColorTable = toml::find_or(saveData, "localGlowColor", {});
    localGlowColor = ImVec4(toml::find_or<float>(localGlowColorTable, "Red", 0.0f), toml::find_or<float>(localGlowColorTable, "Green", 0.255f), toml::find_or<float>(localGlowColorTable, "Blue", 0.7f), toml::find_or<float>(localGlowColorTable, "Alpha", 1.0f));
}

void RWtoml::WriteFile(std::string filename) {
    //Make a variable holds keys and values.
    const toml::value data{{"bAimbot", bAimbot}, {"bGlowHack", bGlowHack},
                           {"bAntiRecoil", bAntiRecoil}, {"bTriggerBot", bTriggerBot}, {"fov", fov},
                           {"enemyGlowColor",    {{"Red", enemyGlowColor.x}, {"Green", enemyGlowColor.y}, {"Blue", enemyGlowColor.z}, {"Alpha", enemyGlowColor.w}}},
                           {"localGlowColor",    {{"Red", localGlowColor.x}, {"Green", localGlowColor.y}, {"Blue", localGlowColor.z}, {"Alpha", localGlowColor.w}}},
                           {"aimSmoothness", aimSmoothness}};
    //Open file and write it in toml syntax.
    std::ofstream file;
    file.open(filename, std::ios::out);
    file << data;
    file.close();
}
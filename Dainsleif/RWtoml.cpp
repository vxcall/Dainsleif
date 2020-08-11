#include "pch.h"
#include "RWtoml.h"
#include "PatternScanner.h"

extern ImVec4 enemyGlowColor, localGlowColor;
extern bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot; //declared in dllmain.cpp
extern float aimSmoothness; //declared in Hacks/Aimbot.cpp
extern int fov; //declared in dllmain.cpp
extern float range;

void RWtoml::ReadSettings(std::string& filename) {
    auto saveData = toml::parse(filename);

    // find specified values associated with one keys, and assign them into each variable.
    bAimbot = toml::find_or<bool>(saveData, "bAimbot", Default::bAimbot);
    aimSmoothness = toml::find_or(saveData, "aimSmoothness", Default::aimSmoothness);
    range = toml::find_or(saveData, "range", Default::range);
    bGlowHack = toml::find_or<bool>(saveData, "bGlowHack", Default::bGlowhack);
    bAntiRecoil = toml::find_or<bool>(saveData, "bAntiRecoil", Default::bAntiRecoil);
    bTriggerBot = toml::find_or<bool>(saveData, "bTriggerBot", Default::bTriggerBot);
    fov = toml::find_or(saveData, "fov", Default::fov);

    auto& enemyGlowColorTable = toml::find_or(saveData, "enemyGlowColor", {});
    enemyGlowColor = ImVec4(toml::find_or(enemyGlowColorTable, "Red", Default::enemyGlowColor.x), toml::find_or(enemyGlowColorTable, "Green", Default::enemyGlowColor.y), toml::find_or(enemyGlowColorTable, "Blue", Default::enemyGlowColor.z), toml::find_or(enemyGlowColorTable, "Alpha", Default::enemyGlowColor.w));

    auto& localGlowColorTable = toml::find_or(saveData, "localGlowColor", {});
    localGlowColor = ImVec4(toml::find_or(localGlowColorTable, "Red", Default::localGlowColor.x), toml::find_or(localGlowColorTable, "Green", Default::localGlowColor.y), toml::find_or(localGlowColorTable, "Blue", Default::localGlowColor.z), toml::find_or(localGlowColorTable, "Alpha", Default::localGlowColor.w));
}

void RWtoml::WriteSettings(std::string& filename) {
    //Make a variable holds keys and values.
    const toml::value data{{"bAimbot", bAimbot}, {"bGlowHack", bGlowHack},
                           {"bAntiRecoil", bAntiRecoil}, {"bTriggerBot", bTriggerBot}, {"fov", fov},
                           {"enemyGlowColor",    {{"Red", enemyGlowColor.x}, {"Green", enemyGlowColor.y}, {"Blue", enemyGlowColor.z}, {"Alpha", enemyGlowColor.w}}},
                           {"localGlowColor",    {{"Red", localGlowColor.x}, {"Green", localGlowColor.y}, {"Blue", localGlowColor.z}, {"Alpha", localGlowColor.w}}},
                           {"aimSmoothness", aimSmoothness}, {"range", range}};
    //Open file and write it in toml syntax.
    std::ofstream file;
    file.open(filename, std::ios::out);
    file << data;
    file.close();
}

void RWtoml::ReadOffsets(std::string& filename) {
    auto saveData = toml::parse(filename);
    dwForceAttack = toml::find_or(saveData, "dwForceAttack", dwForceAttack);
    dwEntityList = toml::find_or(saveData, "dwEntityList", dwEntityList);
    dwGlowObjectManager = toml::find_or(saveData, "dwGlowObjectManager", dwGlowObjectManager);
    dwClientState = toml::find_or(saveData, "dwClientState", dwClientState);
}

void RWtoml::WriteOffsets(std::string& filename)
{
    int64_t a_forceAttack = PatternScanner("client.dll", "\x89\x0D????\x8B\x0D????\x8B\xF2\x8B\xC1\x83\xCE\x04", 2).CalculateOffset(Modules::client);
    int64_t a_entityList = PatternScanner("client.dll", "\xBB????\x83??\x7C?", 1).CalculateOffset(Modules::client);
    int64_t a_glowObjectManager = PatternScanner("client.dll", "\x11?????\x83??\xC7?????????\x0F\x28?????\x68????", 2).CalculateOffset(Modules::client);
    int64_t a_clientState = PatternScanner("engine.dll", "\xA1????\x8B?????\x85?\x74?\x8B?", 1).CalculateOffset(Modules::engine);

    const toml::value data {{"dwForceAttack", a_forceAttack}, {"dwEntityList", a_entityList}, {"dwGlowObjectManager", a_glowObjectManager}, {"dwClientState", a_clientState}};

    std::ofstream file;
    file.open(filename, std::ios::out);
    file << data;
    file.close();
}
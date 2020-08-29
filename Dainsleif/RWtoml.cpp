#include "pch.h"
#include <map>
#include <future>
#include "RWtoml.h"
#include "PatternScanner.h"

extern ImVec4 enemyGlowColor, localGlowColor;
extern bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot, bAntiAFK; //declared in dllmain.cpp
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
    bAntiAFK = toml::find_or<bool>(saveData, "bAntiAFK", Default::bAntiAFK);
    fov = toml::find_or(saveData, "fov", Default::fov);

    auto& enemyGlowColorTable = toml::find_or(saveData, "enemyGlowColor", {});
    enemyGlowColor = ImVec4(toml::find_or(enemyGlowColorTable, "Red", Default::enemyGlowColor.x), toml::find_or(enemyGlowColorTable, "Green", Default::enemyGlowColor.y), toml::find_or(enemyGlowColorTable, "Blue", Default::enemyGlowColor.z), toml::find_or(enemyGlowColorTable, "Alpha", Default::enemyGlowColor.w));

    auto& localGlowColorTable = toml::find_or(saveData, "localGlowColor", {});
    localGlowColor = ImVec4(toml::find_or(localGlowColorTable, "Red", Default::localGlowColor.x), toml::find_or(localGlowColorTable, "Green", Default::localGlowColor.y), toml::find_or(localGlowColorTable, "Blue", Default::localGlowColor.z), toml::find_or(localGlowColorTable, "Alpha", Default::localGlowColor.w));
}

void RWtoml::WriteSettings(std::string& filename) {
    //Make a variable holds keys and values.
    const toml::value data{{"bAimbot", bAimbot}, {"bGlowHack", bGlowHack},
                           {"bAntiRecoil", bAntiRecoil}, {"bTriggerBot", bTriggerBot}, {"bAntiAFK", bAntiAFK}, {"fov", fov},
                           {"enemyGlowColor",    {{"Red", enemyGlowColor.x}, {"Green", enemyGlowColor.y}, {"Blue", enemyGlowColor.z}, {"Alpha", enemyGlowColor.w}}},
                           {"localGlowColor",    {{"Red", localGlowColor.x}, {"Green", localGlowColor.y}, {"Blue", localGlowColor.z}, {"Alpha", localGlowColor.w}}},
                           {"aimSmoothness", aimSmoothness}, {"range", range}};
    //Open file and write it in toml syntax.
    std::ofstream file;
    file.open(filename, std::ios::out);
    file << data;
    file.close();
}

std::map<std::string, uintptr_t> RWtoml::ReadOffsets(std::string& filename) {
    auto saveData = toml::parse(filename);
    dwClientState = toml::find_or(saveData, "dwClientState", dwClientState);
    dwEntityList = toml::find_or(saveData, "dwEntityList", dwEntityList);
    dwLocalPlayer = toml::find_or(saveData, "dwLocalPlayer", dwLocalPlayer);
    dwGlowObjectManager = toml::find_or(saveData, "dwGlowObjectManager", dwGlowObjectManager);
    dwForceAttack = toml::find_or(saveData, "dwForceAttack", dwForceAttack);
    dwForceForward = toml::find_or(saveData, "dwForceForward", dwForceForward);
    dwForceBackward = toml::find_or(saveData, "dwForceBackward", dwForceBackward);
    dwForceRight = toml::find_or(saveData, "dwForceRight", dwForceRight);
    dwForceLeft = toml::find_or(saveData, "dwForceLeft", dwForceLeft);
    dwForceJump = toml::find_or(saveData, "dwForceJump", dwForceJump);

    dwClientState_State = toml::find_or(saveData, "dwClientState_State", dwClientState_State);
    dwClientState_MaxPlayer = toml::find_or(saveData, "dwClientState_MaxPlayer", dwClientState_MaxPlayer);
    dwClientState_ViewAngles = toml::find_or(saveData, "dwClientState_ViewAngles", dwClientState_ViewAngles);
    dwppDirect3DDevice9 = toml::find_or(saveData, "dwppDirect3DDevice9", dwppDirect3DDevice9);
    m_vecOrigin = toml::find_or(saveData, "m_vecOrigin", m_vecOrigin);
    m_iHealth = toml::find_or(saveData, "m_iHealth", m_iHealth);
    m_vecViewOffset = toml::find_or(saveData, "m_vecViewOffset", m_vecViewOffset);
    m_dwBoneMatrix = toml::find_or(saveData, "m_dwBoneMatrix", m_dwBoneMatrix);
    m_iTeamNum = toml::find_or(saveData, "m_iTeamNum", m_iTeamNum);
    m_iGlowIndex = toml::find_or(saveData, "m_iGlowIndex", m_iGlowIndex);
    m_aimPunchAngle = toml::find_or(saveData, "m_aimPunchAngle", m_aimPunchAngle);
    m_iShotsFired = toml::find_or(saveData, "m_iShotsFired", m_iShotsFired);
    m_iCrosshairId = toml::find_or(saveData, "m_iCrosshairId", m_iCrosshairId);
    m_iFOV = toml::find_or(saveData, "m_iFOV", m_iFOV);
    m_bDormant = toml::find_or(saveData, "m_bDormant", m_bDormant);
    m_hActiveWeapon = toml::find_or(saveData, "m_hActiveWeapon", m_hActiveWeapon);
    m_iItemDefinitionIndex = toml::find_or(saveData, "m_iItemDefinitionIndex", m_iItemDefinitionIndex);

    return std::map<std::string, uintptr_t> {{"dwClientState", dwClientState}, {"dwForceAttack", dwForceAttack},
                                             {"dwEntityList", dwEntityList}, {"dwGlowObjectManager", dwGlowObjectManager},
                                             {"dwLocalPlayer", dwLocalPlayer}, {"dwForceForward", dwForceForward},
                                             {"dwForceBackward", dwForceBackward}, {"dwForceRight", dwForceRight},
                                             {"dwForceLeft", dwForceLeft}, {"dwForceJump", dwForceJump}};
}

//This is a wrap function to be passed to std::async
uintptr_t Scan(std::string dllName, std::string signature, int offset, uintptr_t moduleBase, int extra) {
    return PatternScanner(dllName.data(), signature.data(), offset).CalculateOffset(moduleBase, extra);
}

void RWtoml::UpdateOffsets(std::string& filename)
{
    uintptr_t a_entityList = std::async(std::launch::async, Scan, "client.dll", "\xBB????\x83??\x7C?", 1, Modules::client, 0).get();
    uintptr_t a_glowObjectManager = std::async(std::launch::async, Scan, "client.dll", "\x11?????\x83??\xC7?????????\x0F\x28?????\x68????", 2, Modules::client, 0).get();
    uintptr_t a_localPlayer = std::async(std::launch::async, Scan, "client.dll", "\x8D\x34\x85????\x89\x15????\x8B\x41\x08\x8B\x48\x04\x83\xF9\xFF", 3, Modules::client, 4).get();
    uintptr_t a_clientState = std::async(std::launch::async, Scan, "engine.dll", "\xA1????\x8B?????\x85?\x74?\x8B?", 1, Modules::engine, 0).get();
    uintptr_t a_forceAttack = std::async(std::launch::async, Scan, "client.dll", "\x89\x0D????\x8B\x0D????\x8B\xF2\x8B\xC1\x83\xCE\x04", 2, Modules::client, 0).get();
    uintptr_t a_forceBackward = std::async(std::launch::async, Scan, "client.dll", "\x55\x8B\xEC\x51\x53\x8A\x5D\x08", 287, Modules::client, 0).get();
    uintptr_t a_forceForward = std::async(std::launch::async, Scan, "client.dll","\x55\x8B\xEC\x51\x53\x8A\x5D\x08", 245, Modules::client, 0).get();
    uintptr_t a_forceJump = std::async(std::launch::async, Scan, "client.dll", "\x8B\x0D????\x8B\xD6\x8B\xC1\x83\xCA\x02", 2, Modules::client, 0).get();
    uintptr_t a_forceLeft = std::async(std::launch::async, Scan, "client.dll", "\x55\x8B\xEC\x51\x53\x8A\x5D\x08", 465, Modules::client, 0).get();
    uintptr_t a_forceRight = std::async(std::launch::async, Scan, "client.dll", "\x55\x8B\xEC\x51\x53\x8A\x5D\x08", 512, Modules::client, 0).get();
    const toml::value data {
                    {"dwForceAttack", a_forceAttack}, {"dwEntityList", a_entityList},
                    {"dwGlowObjectManager", a_glowObjectManager}, {"dwLocalPlayer", a_localPlayer},
                    {"dwClientState", a_clientState}, {"dwForceBackward", a_forceBackward},
                    {"dwForceForward", a_forceForward}, {"dwForceRight", a_forceRight},
                    {"dwForceJump", a_forceJump},
                    {"dwClientState_State", 0x108}, {"dwForceLeft", a_forceLeft},

                   {"dwClientState_MaxPlayer", 0x388}, {"dwClientState_ViewAngles", 0x4D88},
                    {"dwppDirect3DDevice9", 0xA7030}, {"m_vecOrigin", 0x138},
                    {"m_iHealth", 0x100}, {"m_vecViewOffset", 0x108},
                    {"m_dwBoneMatrix", 0x26A8}, {"m_iTeamNum", 0xF4},
                    {"m_iGlowIndex", 0xA438}, {"m_aimPunchAngle", 0x302C},
                    {"m_iShotsFired", 0xA390}, {"m_iCrosshairId", 0xB3E4},
                    {"m_iFOV", 0x332C}, {"m_bDormant", 0xED},
                    {"m_hActiveWeapon", 0x2EF8}, {"m_iItemDefinitionIndex", 0x2FAA}
    };

    std::ofstream file;
    file.open(filename, std::ios::out);
    file << data;
    file.close();
}

void RWtoml::InitializeOffsets(std::string& filename)
{
    const toml::value data {
                    {"dwClientState", 0x589DD4}, {"dwClientState_State", 0x108}, {"dwForceBackward", 0x31859D8},
                    {"dwForceRight", 0x31859F0}, {"dwForceForward", 0x31859B4},
                    {"dwForceJump", 0x51FE044}, {"dwForceLeft", 0x31859CC},
                    {"dwClientState_MaxPlayer", 0x388}, {"dwClientState_ViewAngles", 0x4D88},
                    {"dwppDirect3DDevice9", 0xA7030}, {"dwEntityList", 0x4D5442C},
                    {"dwLocalPlayer", 0xD3FC5C}, {"dwGlowObjectManager", 0x529C208},
                    {"dwForceAttack", 0x3185984}, {"m_vecOrigin", 0x138},
                    {"m_iHealth", 0x100}, {"m_vecViewOffset", 0x108},
                    {"m_dwBoneMatrix", 0x26A8}, {"m_iTeamNum", 0xF4},
                    {"m_iGlowIndex", 0xA438}, {"m_aimPunchAngle", 0x302C},
                    {"m_iShotsFired", 0xA390}, {"m_iCrosshairId", 0xB3E4},
                    {"m_iFOV", 0x332C}, {"m_bDormant", 0xED},
                    {"m_hActiveWeapon", 0x2EF8}, {"m_iItemDefinitionIndex", 0x2FAA}
    };

    std::ofstream file;
    file.open(filename, std::ios::out);
    file << data;
    file.close();
}
#include "DrawGUI.h"
#include <map>
#include "../Player.h"
#include "../RWtoml.h"

extern bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot, bAntiAFK; //declared in dll.main
extern bool bEsp, bLineOverlay, bRectOverlay; //declared in GraphicHook.main
extern int fov; //declared in dllmain.cpp
extern float aimSmoothness, range; //declared in Hacks/Aimbot.cpp
extern ImVec4 enemyGlowColor, localGlowColor;

extern bool inGame;
extern std::string offsetsFile; //declared in dllmain.cpp



void HelpMarker(const char* title, const std::string& desc)
{
    ImGui::TextDisabled("%s", title);
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc.c_str());
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

bool show_updated_modal = false;

std::map<std::string, uintptr_t> UpdateOffsets() {
    RWtoml::UpdateOffsets(offsetsFile);
    std::map<std::string, uintptr_t> offsets = RWtoml::ReadOffsets(offsetsFile);
    show_updated_modal = true;
    return offsets;
}

void ShowModal(const char* message) {
    ImGui::OpenPopup("Modal");

    // Always center this window when appearing
    ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Modal", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::TextColored((ImVec4)ImColor::HSV(0.57f, 0.6f, 0.8f), "%s", message);
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.57f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.57f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.57f, 0.8f, 0.8f));
        if (ImGui::Button("OK", ImVec2(170, 0))) {
            ImGui::CloseCurrentPopup();
            show_updated_modal = false;
        }
        ImGui::PopStyleColor(3);
        ImGui::SetItemDefaultFocus();
        ImGui::EndPopup();
    }
}

/* NOTE: When a new element which manipulates a hack parameter is added to the menu, you have to modify following 4 places in this project.
         * ReadSettings() in RWtoml.cpp
         * WriteSettings() in RWtoml.cpp
         * setToDefault function
         * DefaultSettings.h
*/

void setToDefault(Hack_label label) {
    switch (label) {
        case ALL:
            bAimbot = Default::bAimbot;
            aimSmoothness = Default::aimSmoothness;
            range = Default::range;
            bGlowHack = Default::bGlowhack;
            enemyGlowColor = Default::enemyGlowColor;
            localGlowColor = Default::localGlowColor;
            bAntiRecoil = Default::bAntiRecoil;
            bTriggerBot = Default::bTriggerBot;
            bAntiAFK = Default::bAntiAFK;
            fov = Default::fov;
            Player::GetLocalPlayer()->SetFOV(Default::fov);
            break;
        case AIMBOT:
            bAimbot = Default::bAimbot;
            aimSmoothness = Default::aimSmoothness;
            range = Default::range;
            break;
        case GLOWHACK:
            bGlowHack = Default::bGlowhack;
            enemyGlowColor = Default::enemyGlowColor;
            localGlowColor = Default::localGlowColor;
            break;
        case ANTIRECOIL:
            bAntiRecoil = Default::bAntiRecoil;
            break;
        case TRIGGERBOT:
            bTriggerBot = Default::bTriggerBot;
            break;
        case FOV:
            fov = Default::fov;
            Player::GetLocalPlayer()->SetFOV(Default::fov);
            break;
        case ANTIAFK:
            bAntiAFK = Default::bAntiAFK;
        case ESP:
            bEsp = Default::bEsp;
    }
}

void ShowMenuBar(std::map<const std::string, bool>& visibleHacks)
{
    static std::map<std::string, uintptr_t> newOffsets;
    if(show_updated_modal) {
        std::string offsetString;
        offsetString.reserve(300); //allocating memory beforehand for performance reason.
        offsetString = "Updating offsets has done!\nNew offsets:\n\n";
        for (auto& offset : newOffsets) {
            offsetString += offset.first;
            offsetString += ": ";
            offsetString += std::to_string(offset.second);
            offsetString += "\n";
        }
        ShowModal(offsetString.data());
    }

    if (ImGui::BeginMenuBar()) {
        // Menu 1
        if (ImGui::BeginMenu("Menu")) {
            // First menu in Menu
            if (ImGui::BeginMenu("Set to default")) {
                if (ImGui::MenuItem("Everything")) {
                    setToDefault(ALL);
                } else if (ImGui::MenuItem("Aim bot")) {
                    setToDefault(AIMBOT);
                } else if (ImGui::MenuItem("Glow hack")){
                    setToDefault(GLOWHACK);
                } else if (ImGui::MenuItem("Anti recoil")) {
                    setToDefault(ANTIRECOIL);
                } else if (ImGui::MenuItem("Trigger bot")) {
                    setToDefault(TRIGGERBOT);
                } else if (ImGui::MenuItem("Anti AFK")) {
                    setToDefault(ANTIAFK);
                } else if (ImGui::MenuItem("FOV")) {
                    setToDefault(FOV);
                } else if (ImGui::MenuItem("ESP")) {
                    setToDefault(ESP);
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Update offsets")) {
                newOffsets = UpdateOffsets();
            }
            if (ImGui::MenuItem("Remove hack"))
                bQuit = true;
            ImGui::EndMenu();
        }
        // Menu 2
        if (ImGui::BeginMenu("Hacks")) {
            for (auto& [key, value] : visibleHacks) {
                ImGui::MenuItem(key.data(), NULL, &value);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void ShowTabMenu(std::map<const std::string, bool>& visibleHacks) {
    Player* localPlayer = Player::GetLocalPlayer();
    static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
    if (ImGui::BeginTabBar("Hack_tab_bar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("Aim bot", &visibleHacks.at("Aim bot")))
        {
            ImGui::Checkbox("Enable Aim bot", &bAimbot);
            ImGui::SliderFloat("Smoothness", &aimSmoothness, 0.005f, 0.4f);
            ImGui::SliderFloat("Range", &range, 1.f, 30.f);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Glow hack", &visibleHacks.at("Glow hack")))
        {
            ImGui::Checkbox("Enable Glow hack", &bGlowHack);
            ImGui::ColorEdit4("Enemy Color", (float*)&enemyGlowColor);
            ImGui::ColorEdit4("Teammate color", (float*)&localGlowColor);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Anti Recoil", &visibleHacks.at("Anti Recoil")))
        {
            ImGui::Checkbox("Enable Anti recoil", &bAntiRecoil);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Trigger bot", &visibleHacks.at("Trigger bot")))
        {
            ImGui::Checkbox("Enable Trigger bot", &bTriggerBot);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Anti AFK", &visibleHacks.at("Anti AFK")))
        {
            ImGui::Checkbox("Enable AntiAFK", &bAntiAFK);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Field of View", &visibleHacks.at("Field of View")))
        {
            if (ImGui::SliderInt("Field of view(FOV)", &fov, 60, 120) && inGame)
                localPlayer->SetFOV(fov);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("ESP          ", &visibleHacks.at("ESP")))
        {
            ImGui::Checkbox("Enable ESP", &bEsp);
            if (bEsp) {
                ImGui::Checkbox("Enable Line overlay", &bLineOverlay);
                ImGui::Checkbox("Enable Rectangle overlay", &bRectOverlay);
            }
            ImGui::EndTabItem();
        }

    }
        ImGui::EndTabBar();
}
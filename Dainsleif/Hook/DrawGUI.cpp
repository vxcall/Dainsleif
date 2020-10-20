#include "DrawGUI.h"
#include <map>
#include "../Player.h"
#include "../Save/OffsetsToml.h"
#include "GraphicHook.h"

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
    OffsetsToml::UpdateOffsets(offsetsFile);
    std::map<std::string, uintptr_t> offsets = OffsetsToml::ReadOffsets(offsetsFile);
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
         * ReadSettings() in OffsetsToml.cpp
         * WriteSettings() in OffsetsToml.cpp
         * setToDefault function
         * DefaultSettings.h
*/

void setToDefault(Hack_label label) {
    switch (label) {
        case ALL:
            HackFlags::bAimbot = Default::bAimbot;
            aimSmoothness = Default::aimSmoothness;
            range = Default::range;
            HackFlags::bGlowHack = Default::bGlowhack;
            enemyGlowColor = Default::enemyGlowColor;
            localGlowColor = Default::localGlowColor;
            HackFlags::bAntiRecoil = Default::bAntiRecoil;
            HackFlags::bTriggerBot = Default::bTriggerBot;
            HackFlags::bAntiAFK = Default::bAntiAFK;
            HackFlags::bEsp = Default::bEsp;
            HackFlags::bLineOverlay = Default::bLineOverlay;
            HackFlags::bRectOverlay = Default::bRectOverlay;
            HackFlags:: bMinimapHack = Default::bMinimapHack;
            fov = Default::fov;
            Player::GetLocalPlayer()->SetFOV(Default::fov);
            break;
        case AIMBOT:
            HackFlags::bAimbot = Default::bAimbot;
            aimSmoothness = Default::aimSmoothness;
            range = Default::range;
            break;
        case GLOWHACK:
            HackFlags::bGlowHack = Default::bGlowhack;
            enemyGlowColor = Default::enemyGlowColor;
            localGlowColor = Default::localGlowColor;
            break;
        case ANTIRECOIL:
            HackFlags::bAntiRecoil = Default::bAntiRecoil;
            break;
        case TRIGGERBOT:
            HackFlags::bTriggerBot = Default::bTriggerBot;
            break;
        case FOV:
            fov = Default::fov;
            Player::GetLocalPlayer()->SetFOV(Default::fov);
            break;
        case ANTIAFK:
            HackFlags::bAntiAFK = Default::bAntiAFK;
        case ESP:
            HackFlags::bEsp = Default::bEsp;
            HackFlags::bLineOverlay = Default::bLineOverlay;
            HackFlags::bRectOverlay = Default::bRectOverlay;
        case MINIMAPHACK:
            HackFlags::bMinimapHack = Default::bMinimapHack;
    }
}

void ShowMenuBar(std::map<std::string, bool>& visibleHacks)
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
                } else if (ImGui::MenuItem("Minimap hack")) {
                    setToDefault(MINIMAPHACK);
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Update offsets")) {
                newOffsets = UpdateOffsets();
            }
            if (ImGui::MenuItem("Remove hack"))
                HackFlags::bQuit = true;
            ImGui::EndMenu();
        }
        // Menu 2
        if (ImGui::BeginMenu("Hacks")) {
            for (auto& [key, value] : visibleHacks) {
                ImGui::MenuItem(key.c_str(), NULL, &value);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void ShowTabMenu(std::map<std::string, bool>& visibleHacks) {
    Player* localPlayer = Player::GetLocalPlayer();
    static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
    if (ImGui::BeginTabBar("Hack_tab_bar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("Aim bot", &visibleHacks.at("Aim Bot")))
        {
            ImGui::Checkbox("Enable Aim bot", &HackFlags::bAimbot);
            ImGui::SliderFloat("Smoothness", &aimSmoothness, 0.005f, 0.4f);
            ImGui::SliderFloat("Range", &range, 1.f, 30.f);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Glow hack", &visibleHacks.at("Glow Hack")))
        {
            ImGui::Checkbox("Enable Glow hack", &HackFlags::bGlowHack);
            ImGui::ColorEdit4("Enemy Color", (float*)&enemyGlowColor);
            ImGui::ColorEdit4("Teammate color", (float*)&localGlowColor);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Anti Recoil", &visibleHacks.at("Anti Recoil")))
        {
            ImGui::Checkbox("Enable Anti recoil", &HackFlags::bAntiRecoil);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Trigger bot", &visibleHacks.at("Trigger Bot")))
        {
            ImGui::Checkbox("Enable Trigger bot", &HackFlags::bTriggerBot);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Anti AFK", &visibleHacks.at("Anti AFK")))
        {
            ImGui::Checkbox("Enable AntiAFK", &HackFlags::bAntiAFK);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Field of View", &visibleHacks.at("Fov")))
        {
            if (ImGui::SliderInt("Field of view(FOV)", &fov, 60, 120) && inGame)
                localPlayer->SetFOV(fov);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("ESP           ", &visibleHacks.at("Esp")))
        {
            ImGui::Checkbox("Enable ESP", &HackFlags::bEsp);
            if (HackFlags::bEsp) {
                ImGui::Checkbox("Enable Line overlay", &HackFlags::bLineOverlay);
                ImGui::Checkbox("Enable Rectangle overlay", &HackFlags::bRectOverlay);
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Minimap hack", &visibleHacks.at("Minimap Hack")))
        {
            ImGui::Checkbox("Enable Minimap hack", &HackFlags::bMinimapHack);
            ImGui::EndTabItem();
        }

    }
        ImGui::EndTabBar();
}
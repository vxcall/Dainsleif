#include "../pch.h"
#include "ImGuiTheme.h"
#include <map>
#include "GraphicHook.h"
#include "../Player.h"
#include "../PatternScanner.h"
#include "../RWtoml.h"


extern bool bQuit, bAimbot, bGlowHack, bAntiRecoil, bTriggerBot, bAntiAFK; //declared in dll.main
extern int fov; //declared in dllmain.cpp
extern float aimSmoothness, range; //declared in Hacks/Aimbot.cpp
extern std::string offsetsFile; //declared in dllmain.cpp
extern bool g_ShowMenu; //decleard in dllmain.cpp
extern ImVec4 enemyGlowColor, localGlowColor;
extern bool inGame;

using endScene = HRESULT (__stdcall*)(IDirect3DDevice9* pDevice);
endScene originalEndScene = nullptr; //An original endscene which is null now.

HWND window = nullptr;
WNDPROC originalWndProc = nullptr;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (g_ShowMenu && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;
    return CallWindowProc(originalWndProc, hWnd, msg, wParam, lParam);
}

static void HelpMarker(char* title, std::string desc)
{
    ImGui::TextDisabled(title);
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc.c_str());
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void InitImGui(IDirect3DDevice9* pDevice)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    LoadFont(io);

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);
}

void ShutdownImGui()
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
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
    }
}

void ShowMenuBar()
{
    static std::map<std::string, uintptr_t> newOffsets;
    if(show_updated_modal) {
        std::string offsetString;
        offsetString.reserve(200); //allocating memory beforehand for performance reason.
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
        if (ImGui::BeginMenu("Menu")) {
            if (ImGui::BeginMenu("Set to default")) {
                if (ImGui::MenuItem("Everything")) {
                    setToDefault(ALL);
                } else if (ImGui::MenuItem("Aim bot")) {
                    setToDefault(AIMBOT);
                } else if (ImGui::MenuItem("Glow hack")){
                    setToDefault(GLOWHACK);
                } else if (ImGui::MenuItem("Anti Recoil")) {
                    setToDefault(ANTIRECOIL);
                } else if (ImGui::MenuItem("Trigger bot")) {
                    setToDefault(TRIGGERBOT);
                } else if (ImGui::MenuItem("Anti AFK")) {
                    setToDefault(ANTIAFK);
                } else if (ImGui::MenuItem("FOV")) {
                    setToDefault(FOV);
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
        ImGui::EndMenuBar();
    }
}

void ShowTabMenu() {
    Player* localPlayer = Player::GetLocalPlayer();
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
    if (ImGui::BeginTabBar("Hack_tab_bar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("Aim bot"))
        {
            ImGui::Checkbox("Enable Aim bot", &bAimbot);
            ImGui::SliderFloat("Smoothness", &aimSmoothness, 0.005f, 0.4f);
            ImGui::SliderFloat("Range", &range, 1.f, 30.f);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Glow hack"))
        {
            ImGui::Checkbox("Enable Glow hack", &bGlowHack);
            ImGui::ColorEdit4("Enemy Color", (float*)&enemyGlowColor);
            ImGui::ColorEdit4("Teammate color", (float*)&localGlowColor);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Anti Recoil"))
        {
            ImGui::Checkbox("Enable Anti recoil", &bAntiRecoil);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Trigger bot"))
        {
            ImGui::Checkbox("Enable Trigger bot", &bTriggerBot);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Field of View"))
        {
            if (ImGui::SliderInt("Field of view(FOV)", &fov, 60, 120) && inGame)
                localPlayer->SetFOV(fov);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Anti AFK"))
        {
            ImGui::Checkbox("Enable AntiAFK", &bAntiAFK);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}

HRESULT __stdcall hookedEndScene(IDirect3DDevice9* pDevice) //A function containing a bunch of rendering process, that is gonna be hooked.
{
    if (g_ShowMenu)
    {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        LoadTheme();

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
        ImGui::Begin("Dainsleif", &g_ShowMenu, window_flags);

        ShowMenuBar(); //tab

        ShowTabMenu(); //main view

        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        HelpMarker("[HACK NOT WORKING?]", "Click \"Update offset\" in the menu bar");
        ImGui::End();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
    return originalEndScene(pDevice);
}

void hookEndScene() {
    auto shaderapidx9 = reinterpret_cast<uintptr_t>(GetModuleHandle("shaderapidx9.dll"));
    IDirect3DDevice9* pDevice = *reinterpret_cast<IDirect3DDevice9**>(shaderapidx9 + dwppDirect3DDevice9);

    D3DDEVICE_CREATION_PARAMETERS parameters;
    pDevice->GetCreationParameters(&parameters);

    window = parameters.hFocusWindow;
    originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));

    InitImGui(pDevice);

    void** vTable = *reinterpret_cast<void***>(pDevice);
    originalEndScene = reinterpret_cast<endScene>(DetourFunction(reinterpret_cast<PBYTE>(vTable[42]), reinterpret_cast<PBYTE>(hookedEndScene)));
}

void unhookEndScene()
{
    DetourRemove(reinterpret_cast<PBYTE>(originalEndScene), reinterpret_cast<PBYTE>(hookedEndScene));

    SetWindowLong(window, GWL_WNDPROC, reinterpret_cast<LONG>(originalWndProc));

    ShutdownImGui();
}
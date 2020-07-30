#include "pch.h"
#include "GraphicHook.h"
#include "LocalPlayer.h"

extern bool bQuit, bAimbot, bGlowHack, bNoRecoil, bTriggerBot; //declared in dll.main
extern uintptr_t moduleBase; //declared in dll.main
extern int fov; //declared in dllmain.cpp
extern float aimSmoothness; //declared in LocalPlayer.cpp
extern std::string filename; //declared in dllmain.cpp
extern ImVec4 enemyGlowColor, localGlowColor; //declared in dll.main

using endScene = HRESULT (__stdcall*)(IDirect3DDevice9* pDevice);
endScene originalEndScene = nullptr; //An original endscene which is null now.

bool g_ShowMenu = false;

HWND window = NULL;
WNDPROC originalWndProc = NULL;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (g_ShowMenu && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;
    return CallWindowProc(originalWndProc, hWnd, msg, wParam, lParam);
}

static void HelpMarker(std::string desc)
{
    ImGui::TextDisabled("(?)");
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

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);
    return;
}

void ShutdownImGui()
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

HRESULT __stdcall hookedEndScene(IDirect3DDevice9* pDevice) //A function containing a bunch of rendering process, that is gonna be hooked.
{
    if (g_ShowMenu)
    {
        LocalPlayer* lp = GetLocalPlayer(moduleBase);
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("HACK4CSGO", &g_ShowMenu);
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("Hack_tab_bar", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("Aim bot"))
            {
                ImGui::Checkbox("Enable Aim bot", &bAimbot);
                ImGui::SliderFloat("Smoothness", &aimSmoothness, 0.01, 0.5);
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
                ImGui::Checkbox("Enable Anti recoil", &bNoRecoil);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Trigger bot"))
            {
                ImGui::Checkbox("Enable Trigger bot", &bTriggerBot);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Field of View"))
            {
                if (ImGui::SliderInt("Field of view(FOV)", &fov, 60, 120))
                    lp->SetFOV(fov);
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::Separator();
        if (ImGui::Button("set everything to default"))
        {
            bAimbot = false;
            bTriggerBot = false;
            bGlowHack = false;
            bNoRecoil = false;
            aimSmoothness = 0.2f;
            enemyGlowColor = ImVec4(0.8f,0.1f,0.15f,1.f);
            localGlowColor = ImVec4(0.f,0.255f,0.7f,1.f);
            fov = 90;
        }
        ImGui::SameLine();
        HelpMarker("Setting file is in the following directory: " + filename);
        if (ImGui::Button("Quit")) bQuit = true;
        ImGui::End();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
    return originalEndScene(pDevice);
}

void hookEndScene() {
    uintptr_t shaderapidx9 = reinterpret_cast<uintptr_t>(GetModuleHandle("shaderapidx9.dll"));
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
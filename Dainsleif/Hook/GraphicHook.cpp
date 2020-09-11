#include "../pch.h"
#include "ImGuiTheme.h"
#include "GraphicHook.h"
#include "DrawGUI.h"
#include <map>
#include "../Hacks/Esp.h"

bool bEsp, bLineOverlay, bRectOverlay;
extern bool g_ShowMenu, inGame; //decleard in dllmain.cpp



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

WindowSize GetWindowSize() {
    RECT size;
    WindowSize windowSize{};
    GetWindowRect(window, &size);
    windowSize.w = size.right - size.left;
    windowSize.w -= 5; //removing pixels sidebar has.
    windowSize.h = size.bottom - size.top;
    windowSize.h -=29; //removing pixels topbar has.
    return windowSize;
}

HRESULT __stdcall hookedEndScene(IDirect3DDevice9* pDevice) //A function containing a bunch of rendering process, that is gonna be hooked.
{
    static Player* oldLocalPlayer = nullptr;
    Player* localPlayer = Player::GetLocalPlayer();
    int gameState = *reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(Modules::engine + dwClientState) + dwClientState_State);

    if (localPlayer != oldLocalPlayer && localPlayer && bEsp)
    {
        std::vector<Player*> playerList = Player::GetAll();
        WindowSize ws = GetWindowSize();
        Esp esp = Esp(localPlayer->GetTeam(), playerList, *pDevice, ws);
        if (bLineOverlay) {
            esp.LineOverlay();
        }

        if (bRectOverlay)
            esp.RectangleOverlay();
    }

    if (gameState != 6 && inGame) {
        oldLocalPlayer = localPlayer;
        inGame = false;
    }


    if (g_ShowMenu)
    {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        LoadTheme();

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
        ImGui::Begin("Dainsleif", &g_ShowMenu, window_flags);

        static std::map<const std::string, bool> visibleHacks = {{"Aim bot", true},
                                                                {"Glow hack", true},
                                                                {"Anti Recoil", true},
                                                                {"Trigger bot", true},
                                                                {"Anti AFK", false},
                                                                {"Field of View", false},
                                                                {"ESP", false}};
        ShowMenuBar(visibleHacks); //tab

        ShowTabMenu(visibleHacks); //main view

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

void hookEndScene()
{
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
#include <iostream>
#include "GraphicHook.h"
#include <d3d9.h>
#include <detours.h>
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

extern bool bAimbot, bGlowHack, bNoRecoil, bTriggerBot;   ////////////////////////////////////////////////////

using endScene = HRESULT (__stdcall*)(IDirect3DDevice9* pDevice);
endScene originalEndScene = nullptr; //An original endscene which is null now.

HWND window = 0;
bool g_ShowMenu = false;

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    DWORD wndProcID;
    GetWindowThreadProcessId(handle, &wndProcID);

    if (GetCurrentProcessId() != wndProcID )
    {
        return TRUE;
    }

    window = handle;
    return FALSE;
}

HWND GetProcessWindow()
{
    EnumWindows(EnumWindowsCallback, NULL);
    return window;
}

WNDPROC originalWndProc = NULL;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (g_ShowMenu && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    {
        return true;
    }
    return CallWindowProc(originalWndProc, hWnd, msg, wParam, lParam);
}

void InitImGui(IDirect3DDevice9* pDevice)
{
    originalWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);
    return;
}

HRESULT __stdcall hookedEndScene(IDirect3DDevice9* pDevice) //A function containing a bunch of rendering process, that is gonna be hooked.
{
    static bool initialized = false;

    if (!initialized)
    {
        InitImGui(pDevice);
        initialized = true;
    }
    else
    {
        if (g_ShowMenu)
        {
            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Menu", &g_ShowMenu);
            ImGui::Checkbox("Aim bot", &bAimbot);
            ImGui::End();

            ImGui::EndFrame();
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        }
    }
    return originalEndScene(pDevice);
}

void hookEndScene() {
    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    if (!pD3D) return;

    D3DPRESENT_PARAMETERS d3dparams = {0};  //set D3DPRESENT_PARAMETERS to pass itself as an argument of createDevice().
    d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dparams.hDeviceWindow = GetProcessWindow();
    d3dparams.Windowed = true;  //need to be interchangeable

    IDirect3DDevice9* pDevice = nullptr; //A variable to be a device in the next line.

    HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetForegroundWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dparams, &pDevice);

    if (FAILED(result) || !pDevice){
        std::cout << "Device is null" << std::endl;
        pD3D->Release();
        return;
    }

    void** vTable = *reinterpret_cast<void***>(pDevice);

    originalEndScene = (endScene)DetourFunction((PBYTE)vTable[42],(PBYTE)hookedEndScene);

    pDevice->Release();
    pD3D->Release();
}

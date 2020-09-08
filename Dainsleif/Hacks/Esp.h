#pragma once
#include "../pch.h"
#include "../Player.h"
#include "../Hook/GraphicHook.h"
#include <optional>
#include <utility>

std::optional<Vector2> WorldToScreen(Vector3 entPos, WindowSize& windowSize);
class Esp {
    const int& localTeamNum;
    std::vector<Player*>& playerList;
    IDirect3DDevice9& pDevice;
    WindowSize& windowSize;

    void DrawOutLineRect(Vector2 top, Vector2 bottom, int thickness, D3DCOLOR color);
    void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color);
    void DrawFilledRect(Vector2 top, Vector2 bottom, D3DCOLOR color);

public:
    Esp(const int& localTeamNum, std::vector<Player*>& playerList, IDirect3DDevice9& pDevice, WindowSize& windowSize)
    : localTeamNum(localTeamNum), playerList(playerList), pDevice(pDevice), windowSize(windowSize){}

    void LineOverlay();
    void RectangleOverlay();
    void HealthOverlay();
};

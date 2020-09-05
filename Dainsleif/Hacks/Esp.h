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


public:
    Esp(const int& localTeamNum, std::vector<Player*>& playerList, IDirect3DDevice9& pDevice, WindowSize& windowSize)
    : localTeamNum(localTeamNum), playerList(playerList), pDevice(pDevice), windowSize(windowSize){}

    void LineOverlay();
    void RectangleOverlay();
};

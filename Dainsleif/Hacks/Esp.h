#pragma once
#include "../pch.h"
#include "../Player.h"
#include "../Hook/GraphicHook.h"
#include <optional>

std::optional<Vector2> WorldToScreen(Vector3 entPos, WindowSize& windowSize);
void DrawLine(LPDIRECT3DDEVICE9 pDevice, int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color);
namespace Esp
{
    void Run(LPDIRECT3DDEVICE9 pDevice, WindowSize windowSize);
}
#include "Esp.h"
#include "../pch.h"

void Esp::DrawFilledRect(IDirect3DDevice9& pDevice, int x, int y, int w, int h, D3DCOLOR color) {
    D3DRECT rect = {x, y, x + w, y + h};
    pDevice.Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}